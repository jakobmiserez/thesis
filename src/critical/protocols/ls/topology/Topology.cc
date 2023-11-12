#include "Topology.h"

#include <queue>
#include <inet/networklayer/common/L3AddressResolver.h>

namespace critical {

namespace ls {

std::function<double(const Topology::Link&)> Topology::DEFAULT_COST_FUNCTION = ([](const Topology::Link& link) {
  return link.getCost();
});
Empty Topology::INITIAL_NO_ACCESS_CONTROL;
Topology::NoAccessControl Topology::NO_ACCESS_CONTROL;


Topology::Topology(): links(0) {

}

Topology::~Topology() {
  clear();
}

void Topology::clear() {
  for (const auto& [_, node]: routerNodes) {
    delete node;
  }
  routerNodes.clear();
  for (const auto& node: subnetNodes) {
    delete node;
  }
  subnetNodes.clear();
  links = 0;
}

Topology::Node* Topology::addRouterNode(const RouterId& routerId) {
  RouterNode* node = new RouterNode(routerId);
  routerNodes[routerId] = node;
  return node;
}

Topology::Node* Topology::addRouterNodeIfNotExists(const RouterId& routerId) {
  auto it = routerNodes.find(routerId);
  if (it != routerNodes.end()) {
    return it->second;
  }
  return addRouterNode(routerId);
}

Topology::Node* Topology::addSubnetNode(const inet::Ipv6Address& networkPrefix, uint8_t prefixLength) {
  SubnetNode* node = new SubnetNode(networkPrefix, prefixLength);
  subnetNodes.insert(node);
  return node;
}

void Topology::addLink(int id, Node* from, Node* to, double cost) {
  from->outgoingLinks.emplace_back(id, from, to, cost);
  links++;
}


template <class T>
void Topology::computeDistances(Node* from, T initial, const PathAccessControl<T>& accessControl, std::function<double(const Link&)> costf) {
  return computeDistance(from, nullptr, initial, accessControl, costf);
}

template <class T>
void Topology::computeDistances(Node* from, T initial, const PathAccessControl<T>& accessControl) {
  return computeDistances(from, initial, accessControl, DEFAULT_COST_FUNCTION);
}

void Topology::computeDistances(Node* from, std::function<double(const Link&)> costf) {
  return computeDistances(from, INITIAL_NO_ACCESS_CONTROL, NO_ACCESS_CONTROL, costf);
}

void Topology::computeDistances(Node* from) {
  return computeDistances(from, DEFAULT_COST_FUNCTION);
}
      
   
template <class T>
void Topology::computeDistance(Node* from, Node* to, T initial, const PathAccessControl<T>& accessControl, std::function<double(const Link&)> costf) {
  EV_INFO << "(TOPOLOGY) Computing distances\n";
  
  // Initialize all nodes by clearing their path calculation parameters
  for (auto& [_, node]: routerNodes) {
    node->clear();
  }
  for (auto& node: subnetNodes) {
    node->clear();
  }

  // Inititalize the first node
  from->data.metric = 0;
  from->data.originalMetric = 0;

  //
  // Perform Dijkstra with additional link access control
  //

  std::priority_queue<QueuedNode<T>, std::vector<QueuedNode<T>>, std::greater<QueuedNode<T>>> queue;
  queue.push({ from, 0, initial });

  while (!queue.empty()) {
    // Copy and pop the first element of the queue: this is the node 
    // that we are currently visiting
    QueuedNode<T> head = queue.top();
    queue.pop();

    // Check if the node is already visited, we don't have to visit the same 
    // node twice
    if (head.node->data.visited) {
      continue;
    }
    head.node->data.visited = true;

    // If our specific destination is reached, we can stop early
    if (head.node == to) {
      buildPath(from, to);
      return;
    }

    for (auto& link: head.node->outgoingLinks) {
      // If the destination of the link was already visited, or
      // if this link is not allowed according to the access control, we don't need to 
      // visit this edge
      if (link.to->data.visited || !accessControl.canAccessLink(link, head)) {
        continue;
      }

      // Compute metric and update accordingly
      double metric = costf(link) + head.metric;
      if (metric < link.to->data.metric) {
        // Update the path information
        link.to->data.metric = metric;
        link.to->data.incoming = &link;
        link.to->data.hops = head.node->data.hops + 1;
        link.to->data.originalMetric = head.node->data.originalMetric + link.cost;

        // Keep track of the first hop routerId after the starting node
        if (head.node == from) {
          link.to->data.firstHop = link.to->routerId;
        }
        else {
          link.to->data.firstHop = head.node->data.firstHop;
        }

        // Update the additional access parameters
        T newParams = accessControl.updateAfterAccess(link, head);

        // Add a new entry in the queue
        queue.push({link.to, metric, newParams});
      }
    }
  }
}

template <class T>
void Topology::computeDistance(Node* from, Node* to, T initial, const PathAccessControl<T>& accessControl) {
  computeDistance(from, to, initial, accessControl, DEFAULT_COST_FUNCTION);
}

void Topology::computeDistance(Node* from, Node* to, std::function<double(const Link&)> costf) {
  computeDistance(from, to, INITIAL_NO_ACCESS_CONTROL, NO_ACCESS_CONTROL, costf);
}

void Topology::computeDistance(Node* from, Node* to) {
  computeDistance(from, to, INITIAL_NO_ACCESS_CONTROL, NO_ACCESS_CONTROL, DEFAULT_COST_FUNCTION);
}

Topology::Node* Topology::getNodeWithId(const RouterId& routerId) const {
  auto node = routerNodes.find(routerId);
  if (node == routerNodes.end())
    throw cRuntimeError("Topology: could not find node with %s", routerId.str().c_str());
  return node->second;
}
      
Topology::Node* Topology::getDestinationNode(const inet::Ipv6Address& destination) const {
  auto it = subnetNodes.begin();
  Node* res = nullptr;
  while (it != subnetNodes.end() && res == nullptr) {
    SubnetNode* node = (*it);
    if (node->isDestinationFor(destination)) {
      res = node;
    }
    ++it;
  }
  return res;
}

void Topology::print() const {
  EV_INFO << "Graph of " << (subnetNodes.size() + routerNodes.size()) << "\n";
  inet::L3AddressResolver resolver;
  for (const auto& [_, vertex]: routerNodes) {

    cModule* mod = resolver.findHostWithAddress(vertex->routerId);
    EV_INFO << "  " << mod->getName() << "\n";

    for (const auto& link: vertex->outgoingLinks) {
      std::string name;
      if (link.to->isSubnetNode()) {
        name = "(subnet)";
      }
      else {
        name = resolver.findHostWithAddress(link.to->routerId)->getName();
      }
      EV_INFO << "  |-> " << name.c_str() << " (" << link.cost << ")\n";
    }
    EV_INFO << "\n";
  }
}

void Topology::printPath() const {
  EV_INFO << "Path of " << path.size() << ": ";
  if (path.size() > 0) {
    inet::L3AddressResolver resolver;

    for (const auto& link: path) {
      Node* from = link->from;
      Node* to = link->to;
      EV_INFO << "(" << (from->routerId.isUnspecified() ? "<unspec>" : resolver.findHostWithAddress(from->routerId)->getFullPath());
      EV_INFO << "," << (to->routerId.isUnspecified() ? "<unspec>" : resolver.findHostWithAddress(to->routerId)->getFullPath()) << " -> ";
    }
  }
  EV_INFO << "\n";
}

void Topology::buildPath(Node* from, Node* to) {
  path.clear();
  Node* current = to;
  while (current != from) {
    path.push_back(current->data.incoming);
    current = current->data.incoming->from;
  }

  for (int i = 0; i < path.size() / 2; i++) {
    int j = path.size() - 1 - i;
    const Link* temp = path[j];
    path[j] = path[i];
    path[i] = temp;
  }
}

uint64_t Topology::computeMemoryFootprint() const {
  return routerNodes.size() * sizeof(RouterNode) + subnetNodes.size() * sizeof(SubnetNode) + links * sizeof(Link);
}

// Explicitly instantiate generic methods 
// These are the methods regarding access control, and we only need those 
// for two types: FlowParameters and Empty

template void Topology::computeDistances(Node* from, Empty initial, const PathAccessControl<Empty>& accessControl, std::function<double(const Link&)> costf);
template void Topology::computeDistances(Node* from, Empty initial, const PathAccessControl<Empty>& accessControl);
template void Topology::computeDistance(Node* from, Node* to, Empty initial, const PathAccessControl<Empty>& accessControl, std::function<double(const Link&)> costf);
template void Topology::computeDistance(Node* from, Node* to, Empty initial, const PathAccessControl<Empty>& accessControl);

template void Topology::computeDistances(Node* from, FlowParameters initial, const PathAccessControl<FlowParameters>& accessControl, std::function<double(const Link&)> costf);
template void Topology::computeDistances(Node* from, FlowParameters initial, const PathAccessControl<FlowParameters>& accessControl);
template void Topology::computeDistance(Node* from, Node* to, FlowParameters initial, const PathAccessControl<FlowParameters>& accessControl, std::function<double(const Link&)> costf);
template void Topology::computeDistance(Node* from, Node* to, FlowParameters initial, const PathAccessControl<FlowParameters>& accessControl);

}

}