#include "LsRouter.h"

#include "critical/protocols/ls/LsMessageHandler.h"
#include "critical/flows/Flow.h"

namespace critical {

namespace ls {

LsRouter::LsRouter(CriticalProtocol* protocol)
: MinimalLsRouter(protocol),
  qosLsas(lsas, protocol) {

}

LsRouter::~LsRouter() {

}

void LsRouter::start(double delay) {
  MinimalLsRouter::start(delay);
  qosLsas.init();

  // Listen to the consumption 
  for (auto& p: ports) {
    p.addListener(this);
  }
}

LsRouter::RouteResult LsRouter::startRouting(
  const inet::Ipv6Address& source, 
  const inet::Ipv6Address& dest, 
  uint32_t label, 
  uint64_t delay,
  uint64_t bandwidth,
  uint64_t burst
) {
  Flow flow(source, dest, label, delay, bandwidth, burst);

  EV_INFO << "Routing for: " << flow.id << "\n";

  std::optional<std::vector<const Topology::Link*>> path;

  const auto& algorithm = getParams().lsAlgorithm;
  switch (algorithm)  {
    case LsAlgorithm::LARAC: {
      path = queueLevelTopology.larac(routerId, flow);
    } break;
    case LsAlgorithm::MIN_DELAY:
    default: {
      path = queueLevelTopology.mindelay(routerId, flow);
    } break;
  }

  if (!path.has_value()) {
    protocol->straightFails++;
    return FAILED;
  }

  queueLevelTopology.printPath();
  primaryPathTable.insertPath(flow, path.value());

  auto info = QueueLevelTopologyLinkEncoding::decodeLink(path.value().at(0)->getId());
  if (!getPortById(info.linkId)->canAllocateFlow(info.queue, flow.params)) {
    throw cRuntimeError("Your path computation is garbage\n");
  }

  protocol->sendPacketLo(packetCreator.createEmbedPacket(flow, path.value()));
  return ONGOING;
}

void LsRouter::startFreeing(
  const inet::Ipv6Address& source, 
  const inet::Ipv6Address& dest, 
  uint32_t label
) {

}

void LsRouter::rebuild() {
  MinimalLsRouter::rebuild();
  EV_INFO << "(LSROUTER) Rebuilding\n"; 
  rebuildQueueLevelTopology();
}

void LsRouter::rebuildQueueLevelTopology() {
  EV_INFO << "(LSROUTER) Rebuilding QoS graph\n";
  queueLevelTopology.build(lsas, qosLsas);
  EV_INFO << "(LSROUTER) Rebuilt QoS graph\n";
  //queueLevelTopology.print();
}

void LsRouter::onConsumptionChange(int id, bool significant, bool up) {
  auto strat = getParams().lsUpdateStrategy;
  if ((strat == CONSUMPTION || strat == HYBRID) && significant) {
    if (getNeighborTable().getNeighbor(id).isFullyAdjacent()) {
      sendOutQosLsa(id);
    }
  }
}

void LsRouter::handleLinkFailure(const RouterId& at, const std::set<int> removedLinks) {
  EV_INFO << "(LS ROUTER) Handling link failure\n";

  for (const auto& link: removedLinks) {
    std::vector<Flow> reroutes = primaryPathTable.removeAllGoingThrough(at, link);
    for (const auto& flow: reroutes) {
      FlowTableEntry entry = protocol->getFlowTable().deleteFlow(flow.id.src, flow.id.dest, flow.id.label);
      getPortById(entry.data.nextInterface)->freeFlow(entry.data.queueNumber, entry.data.params);
      reroute(flow);
    }

    std::vector<Flow> deletes = secondaryPathTable.removeAllGoingThrough(at, link);
    for (const auto& flow: deletes) {
      FlowTableEntry entry = protocol->getFlowTable().deleteFlow(flow.id.src, flow.id.dest, flow.id.label);
      getPortById(entry.data.nextInterface)->freeFlow(entry.data.queueNumber, entry.data.params);
    }
  }
}

void LsRouter::sendOutQosLsa(int interfaceId) {
  EV_INFO << "(LS ROUTER) Sending out QoSLSAs\n";

  ASSERT(getPortById(interfaceId)->check());
  inet::Packet* lsa = packetCreator.createQosLsa(interfaceId);
  for (const auto& [id, neighbor]: neighborTable) {
    if (neighbor.isFullyAdjacent()) {
      messageHandler->sendPacket(lsa->dup(), neighbor.neighborAddress, id);
    }
  }
  delete lsa;
}

TopLevelMessageHandler* LsRouter::createMessageHandler() {
  return new LsMessageHandler(protocol);
}

}

}
