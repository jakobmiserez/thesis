#include "MinimalLsRouter.h"
#include "MinimalLsMessageHandler.h"

#include "critical/CriticalProtocol.h"


namespace critical {

namespace ls {

MinimalLsRouter::MinimalLsRouter(CriticalProtocol* protocol)
: RouterBase(protocol), packetCreator(this), updatesAutomatically(false) {
  lsas.addListener(this);
}

MinimalLsRouter::~MinimalLsRouter() {
  lsas.removeListener(this);
}


void MinimalLsRouter::start(double delay) {
  RouterBase::start(delay);

  // Initialize interfaces
  for (auto& interface: interfaces) {
    neighborTable.addNeighbor(interface);
  }

  // Initialize routerId
  routerId = interfaces[0]->getNetworkAddress().toIpv6();
  for (int i = 1; i < interfaces.size(); i++) {
    RouterId id = interfaces[i]->getNetworkAddress().toIpv6();
    if (id < routerId) {
      routerId = id;
    }
  }

  EV_INFO << "(MINIMAL LSROUTER) RouterId is " << routerId << "\n";
}

void MinimalLsRouter::rebuild() {
  EV_INFO << "(MINIMAL LSROUTER) Rebuilding\n"; 
  rebuildRoutingTable(); 
}

TopLevelMessageHandler* MinimalLsRouter::createMessageHandler() {
  return new MinimalLsMessageHandler(protocol);
}

void MinimalLsRouter::rebuildRoutingTable() {
  EV_INFO << "(MINIMAL LSROUTER) Rebuilding routing table\n";
  //Delete all routes
  inet::IRoute* defaultRoute = ipRoutingTable->getDefaultRoute();
  int routesToDelete  = ipRoutingTable->getNumRoutes();
  int j = 0;

  while (routesToDelete > 0) {
    inet::IRoute* route = ipRoutingTable->getRoute(j);
    if (route != defaultRoute && !route->getNextHopAsGeneric().isUnspecified()) {
      delete ipRoutingTable->removeRoute(route);
    }
    else {
      j++;
    }
    routesToDelete--;
  }

  // Build the network graph and compute the distances 
  topology.build(lsas);
  //topology.print();
  topology.computeDistances(routerId);

  for (const auto& net: topology.getSubnetNodes()) {
    if (net->getData().firstHop.isUnspecified()) {
      continue;
    }
    
    inet::IRoute* route = ipRoutingTable->createRoute();
    route->setDestination(net->getNetworkPrefix());
    route->setPrefixLength((int)net->getPrefixLength());
    route->setMetric(net->getData().metric);
    
    const NeighborTable::Neighbor* nextHop = neighborTable.findNeighbor(net->getData().firstHop);
    route->setNextHop(nextHop->neighborAddress);
    route->setInterface(protocol->getInterfaceTable()->getInterfaceById(nextHop->interfaceId));

    EV_INFO << "(MINIMAL LSROUTER) Adding route: " << route->getDestinationAsGeneric().toIpv6() << "/" << route->getPrefixLength() << "\n";

    ipRoutingTable->addRoute(route);
  }
}

void MinimalLsRouter::handleLinkFailure(int interfaceId) {
  EV_INFO << "(MINIMAL LSROUTER) Handling link failure\n";
  neighborTable.goDown(interfaceId);

  inet::Packet* lsa = packetCreator.createLsa();
  lsas.insertLsa(lsa->peekAtFront<LsaPacket>().get());

  for (const auto& [id, neighbor]: neighborTable) {
    if (neighbor.isFullyAdjacent()) {
      messageHandler->sendPacket(lsa->dup(), neighbor.neighborAddress, neighbor.interfaceId);
    }
  }

  delete lsa;
}

void MinimalLsRouter::onLsaAdded(const Lsa& lsa) {
  if (updatesAutomatically) {
    rebuild();
  }
}
  
void MinimalLsRouter::onLsaUpdate(const Lsa& lsa, const LsaConnectivityChanges& connectivity) {
  EV_INFO << "(MINIMAL LSROUTER) Got an LSA update\n";
  if (updatesAutomatically && connectivity.connectivityChanged()) {
    EV_INFO << "(MINIMAL LSROUTER) Rebuilding after connectivitychange\n";
    rebuild();
    if (connectivity.removedLinks.size() > 0) {
      handleLinkFailure(lsa.id, connectivity.removedLinks);
    }
  }
}

void MinimalLsRouter::handleLinkFailure(const RouterId& at, const std::set<int> removedLinks) {
  // Do nothing, becaus rebuild will already be called at this point.
  // However, this method could be interesting to override if specific paths need 
  // rerouting or resources need to be freed.
}

}

}