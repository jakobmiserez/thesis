#include "NetworkTopology.h"

#include "critical/protocols/ls/lsa/LsaDatabase.h"
#include "critical/protocols/ls/topology/accesscontrol/DisjointAccessControl.h"

namespace critical {

namespace ls {

void NetworkTopology::build(const LsaDatabase& lsas) {
  clear();

  for (const auto& [id, lsa]: lsas) {
    Node* node = addRouterNodeIfNotExists(id);

    for (const auto& link: lsa.links) {
      if (link.isLinkToRouter()) {
        // Only add the link if both parties agree on adjacency
        if (lsas.getLsaOf(link.to).hasNeighbor(id)) {
          Node* neighbor = addRouterNodeIfNotExists(link.to);
          addLink(link.linkId, node, neighbor, link.cost);
        }
      }
      else {
        Node* neighbor = addSubnetNode(link.networkAddress, link.prefixLength);
        addLink(link.linkId, node, neighbor, link.cost);
        addLink(0, neighbor, node, link.cost);
      }
    }
  }
}

void NetworkTopology::computeDistances(const RouterId& from) {
  Topology::computeDistances(getNodeWithId(from));
  lastDestinationAddress = inet::Ipv6Address::UNSPECIFIED_ADDRESS;
}

void NetworkTopology::computeAlternatives(const RouterId& from, const inet::Ipv6Address& dest) {
  if (dest == lastDestinationAddress) {
    EV_INFO << "(NETWORK TOPOLOGY) Caching computations for routes to " << dest << "\n";
    return;
  }
  EV_INFO << "(NETWORK TOPOLOGY) Computing routes to " << dest << "\n";

  // Make sure that the alternative routes don't go through this node itself
  DisjointAccessControl ac;
  ac.add(from);

  Topology::computeDistances(getDestinationNode(dest), Empty(), ac);
  lastDestinationAddress = dest;
}

double NetworkTopology::getAlternativeRouteCost(const RouterId& from, const inet::Ipv6Address& dest, const RouterId& through) {
  computeAlternatives(from, dest);

  EV_INFO << inet::L3AddressResolver().findHostWithAddress(through)->getName() << "\n";
  return getNodeWithId(through)->getData().metric;
}
  
}

}