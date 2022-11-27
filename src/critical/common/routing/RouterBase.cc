#include "RouterBase.h"

#include "critical/CriticalProtocol.h"
#include "critical/common/util/ModuleHelpers.h"

#include <inet/networklayer/contract/IInterfaceTable.h>
#include <inet/networklayer/ipv6/Ipv6Route.h>

using namespace omnetpp;

namespace critical {

RouterBase::RouterBase(CriticalProtocol* protocol) 
: Parameterizable(protocol),
  protocol(protocol), 
  ipRoutingTable(protocol->getRoutingTable()) {

  timer = new cMessage("CRITICAL::TIMER");
  initializeInterfaces();
  
  const int queues = getParams().numQueues - 1;
  portIds.reserve(interfaces.size());
  ports.reserve(interfaces.size());
  for (const auto& interface: interfaces) {
    LinkParameters params = getLinkParameters(interface);
    
    PredictablePort& port = ports.emplace_back(interface->getInterfaceId(), queues, protocol);
    
    idToPort[port.getId()] = &port;
    portIds.emplace_back(port.getId());
    port.initialize(params.rate);
    port.setLinkDelayFromSeconds(params.delay);
  }
}

RouterBase::~RouterBase() {
  messageHandler->clearTimer(timer);
  delete timer;
  delete messageHandler;
}

void RouterBase::start(double delay) {
  messageHandler = createMessageHandler();
  messageHandler->startTimer(timer, delay);
  EV_INFO << "(ROUTERBASE) Starting router\n";
}

void RouterBase::initializeInterfaces() {
  const inet::IInterfaceTable* interfaces = protocol->getInterfaceTable();

  for (int i = 0; i < interfaces->getNumInterfaces(); i++) {
    inet::InterfaceEntry* interface = interfaces->getInterface(i);

    // Add the interface if it is not a loopback address and it uses IPv6
    if (!interface->isLoopback() && interface->getNetworkAddress().getType() == inet::L3Address::IPv6) {
      this->interfaces.emplace_back(interface);
    }
  }
}

inet::InterfaceEntry* RouterBase::getInterfaceById(const int id) const {
  return protocol->getInterfaceTable()->getInterfaceById(id);
}

bool RouterBase::isDestinationRouterFor(const inet::Ipv6Address& address) {
  // Check if the address is a local address of the router 
  if (ipRoutingTable->isLocalAddress(address)) {
    return true;
  }

  // Check if the address can be reached directly from this router.
  // If so, this router is the final hop to the destination.
  const inet::IRoute* route = ipRoutingTable->findBestMatchingRoute(address);
  if (route != nullptr && route->getNextHopAsGeneric().isUnspecified()) {
    return true;
  }

  return false;
}

bool RouterBase::isLocalAddress(const inet::Ipv6Address& address) {
  return ipRoutingTable->isLocalAddress(address);
}

std::optional<Route> RouterBase::getRouteFor(const inet::Ipv6Address& address) {
  inet::IRoute* route = ipRoutingTable->findBestMatchingRoute(address);
  if (route == nullptr) {
    return {};
  }
  return Route::from(route);
}

void RouterBase::reroute(const FlowId& flow, const FlowParameters& params) {
  protocol->initiateRouting(flow.src, flow.dest, flow.label, params.delay, params.rate, params.burst);
}

RouterBase::LinkParameters RouterBase::getLinkParameters(inet::InterfaceEntry* entry) {
  cChannel* channel = ModuleHelpers::getChannel(entry);
  return { channel->par("delay").doubleValue(), channel->par("datarate").doubleValue() };
}

}