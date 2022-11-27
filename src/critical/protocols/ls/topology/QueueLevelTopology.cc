#include "QueueLevelTopology.h"

#include "critical/CriticalProtocol.h"
#include "critical/protocols/ls/lsa/LsaDatabase.h"
#include "critical/protocols/ls/lsa/QosLsaDatabase.h"
#include "critical/protocols/ls/topology/accesscontrol/Meta.h"
#include "critical/protocols/ls/topology/accesscontrol/QueueAccessControl.h"

namespace critical {

namespace ls {

void QueueLevelTopology::build(LsaDatabase& lsas, QosLsaDatabase& qos) {
  clear();
  accessControl.setQosLsaDatabase(&qos);

  for (const auto& [id, lsa]: lsas) {
    Node* node = addRouterNodeIfNotExists(id);

    for (const auto& link: lsa.links) {
      Node* neighbor;
      if (link.isLinkToRouter()) 
        neighbor = addRouterNodeIfNotExists(link.to);
      else 
        neighbor = addSubnetNode(link.networkAddress, link.prefixLength);

      const auto linkControl = qos.getQueueStates(id, link.linkId);
      for (int i = 0; i < linkControl->getNumQueues(); i++) {
        auto id = QueueLevelTopologyLinkEncoding::encodeLink(link.linkId, i);
        addLink(id, node, neighbor, linkControl->getTotalDelay(i));
      }
    }
  }
}

std::optional<std::vector<const Topology::Link*>> QueueLevelTopology::larac(const RouterId& from, const Flow& flow, std::initializer_list<Topology::PathAccessControl<Empty>*> empties) {
  And ac(&accessControl, empties);

  Node* node = getNodeWithId(from);
  Node* dest = getDestinationNode(flow.id.dest);

  EV_INFO << "(LARAC) Running LARAC algorithm to find a suitable path\n";
  auto cf = [](const Link& link) { return 1; }; // return original cost
  auto df = [](const Link& link) { return link.getCost(); }; // return original delay

  // Perform Dijkstra min-hop
  computeDistance(node, dest, flow.params, ac, cf);
  if (dest->isReachable() && dest->getData().originalMetric <= flow.params.delay) {
    return getPath();
  }
  auto pc = computePathParameters(dest);

  // Perform dijkstra using pure delay costs.
  // If this gives no solution, then there is simply not a single path 
  // possible.
  computeDistance(node, dest, flow.params, ac, df);
  if (dest->getData().originalMetric > flow.params.delay) {
    return {};
  }
  auto pd = computePathParameters(dest);

  while (true) {
    double lambda = (pd.cost - pc.cost) / (pd.delay - pc.delay);
    auto costf = [lambda](const Link& l) { return 1 + lambda * l.getCost(); };

    computeDistance(node, dest, flow.params, ac, costf);
    auto r = computePathParameters(dest);
    if (!dest->isReachable()) {
      return pd.path;
    }

    double pcnew = recomputeCost(pc.path, costf);

    if (pcnew == r.cost) {
      return pd.path;
    }
    if (r.delay <= flow.params.delay) {
      pd = r;
    }
    else {
      pc = r;
    }
  }
}

std::optional<std::vector<const Topology::Link*>> QueueLevelTopology::mindelay(const RouterId& from, const Flow& flow, std::initializer_list<Topology::PathAccessControl<Empty>*> empties) {
  And ac(&accessControl, empties);

  Node* node = getNodeWithId(from);
  Node* dest = getDestinationNode(flow.id.dest);

  computeDistance(node, dest, flow.params, ac);
  
  if (dest->isReachable() && dest->getData().originalMetric <= flow.params.delay) {
    return getPath();
  }
  return {};
}

std::vector<const Topology::Link*> QueueLevelTopology::reconstructPath(const LsEmbedPacket* embedding) const {
  std::vector<const Link*> res;
  res.reserve(embedding->getPathArraySize());

  const Node* current = getNodeWithId(embedding->getRouterId());
  for (size_t i = 0; i < embedding->getPathArraySize(); i++) {
    const auto& decodedLink = embedding->getPath(i);

    const Link* link = current->findLink(QueueLevelTopologyLinkEncoding::encodeLink(decodedLink));
    res.push_back(link);
    current = link->getTo();
  }
  return res;
}


QueueLevelTopology::PathParameters QueueLevelTopology::computePathParameters(Node* dest) {
  PathParameters res;
  res.cost = dest->getData().metric;
  res.delay = dest->getData().originalMetric;
  res.path = getPath();
  return res;
}

double QueueLevelTopology::recomputeCost(const std::vector<const Link*>& path, std::function<double(const Link&)> costf) {
  double cost = 0;
  for (const auto& link: path) {
    cost += costf(*link);
  }
  return cost;
}

}

}