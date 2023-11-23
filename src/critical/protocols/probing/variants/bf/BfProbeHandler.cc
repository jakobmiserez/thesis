#include "BfProbeHandler.h"

#include "critical/CriticalProtocol.h"
#include "critical/protocols/probing/ProbingRouter.h"
#include "critical/protocols/probing/packets/PacketCreator.h"
#include "critical/common/util/FuncList.h"
#include "critical/common/packet/OriginalSourceTag_m.h"

#include <inet/networklayer/common/L3AddressResolver.h>

namespace critical {

namespace probing {

BfProbeHandler::BfProbeHandler(StatefulMessageHandler<BfState>* parent)
: SharedStatePacketHandler<FlowProbePacket, BfState, ProbingRouter>(parent, PROBE_PROBE) {

}

BfProbeHandler::~BfProbeHandler() {

}

bool BfProbeHandler::handleMultiplexedPacket(const inet::Packet* const packet) {
  preprocessPacket(packet);

  EV_INFO << "(BF PROBE HANDLER) Handling probe packet\n";
  EV_INFO << "(BF PROBE HANDLER) "  << packetData.data->getFlow() << "\n";

  //inet::L3AddressResolver resolver;
  //EV_INFO << "(BF PROBE HANDLER) Handling probe packet from " << resolver.findHostWithAddress(packetData.sourceAddress)->getFullPath() << "(" << packetData.sourceInterface << ")\n";

  auto& state = getSharedState();
  auto data = getPacketData(packet);

  // Check if the probing packet is late
  if (getFlowTable().contains(state.flow) || router->getExternalFlows().contains(state.flow)) {
    return handleLate();
  }

  // This is not the first probe packet to arrive
  if (state.unconfirmedProbes.size() > 0) {
    if (getParams().probingFastPrune || state.isFirstHop) {
      EV_INFO << "(BF PROBE HANDLER) Fast pruning upon late probe\n";
      // Fast prune 
      // Immediately send a prune backet back to free allocated resources
      sendPacketBack(PacketCreator::createFlowPrunePacket(state.flow));
      return false;
    }
    else {
      EV_INFO << "(BF PROBE HANDLER) Keeping packet in queue\n";
      // Keep it in a queue
      // This temporary freezes the resources allocated up until this packet
      inet::Packet* dup = packet->dup();
      OriginalSourceTag* tag = dup->addTagIfAbsent<OriginalSourceTag>();
      tag->setOriginalInterface(packetData.sourceInterface);
      tag->setOriginalSourceAddress(packetData.sourceAddress.toIpv6());
      state.queue.push_back(dup);
      return false;
    }
  }

  setParams(packetData.data);

  // Check if the router is the destination router
  if (router->isDestinationRouterFor(data->getFlow().dest)) {
    return handleAtDestination();
  }

  return handleProbe();
}

void BfProbeHandler::setParams(const FlowProbePacket* packet) {
  auto& state = getSharedState();
  state.params = packet->getParams();
  state.interfaceId = packetData.sourceInterface;
  state.isFirstHop = packetData.sourceInterface == pparent->getProtocol()->getLo()->getInterfaceId();
}

bool BfProbeHandler::handleAtDestination() {
  EV_INFO << "(BF PROBE HANDLER) Probing packet reached final destination router!\n";

  auto& state = getSharedState();

  uint64_t accumulatedDelay = packetData.data->getStats().accumulatedDelay;

  ASSERT(accumulatedDelay <= packetData.data->getParams().delay);

  int queue = -1;
  int id = -1;

  if (!router->isLocalAddress(state.flow.dest)) {
    // Allocate the flow in the flow table 

    id = router->getRouteFor(state.flow.dest)->interface;

    auto port = router->getPortById(id);
    auto links = port->getPossibleLinks(state.params, accumulatedDelay);
    if (links.empty()) {
      sendPacketBack(PacketCreator::createFlowPrunePacket(state.flow));
      return true;
    }
    auto link = links[0];
    link.allocate(state.params);

    queue = link.getQueue();

    getFlowTable().embedFlow(
      state.flow,
      state.params,
      id,
      state.flow.dest,
      packetData.sourceInterface,
      queue,
      true,
      true
    );
  }

  getProtocol()->onProbeReservation(state.flow, 1);

  getProtocol()->onPathSignaling(state.flow);

  // Send confirmation packet
  sendPacketBack(PacketCreator::createFlowConfirmPacket(state.flow));

  // The routing protocol is finished, so no need to multiplex anymore for this flow request
  return true;
}

bool BfProbeHandler::handleLate() {
  EV_INFO << "(BF PROBE HANDLER) Received a late probing request, sending a prune back\n";
  auto& state = getSharedState();

  // Send back prune packet
  sendPacketBack(PacketCreator::createFlowPrunePacket(state.flow));

  // The routing protocol is finished, so no need to multiplex
  return true;
}

bool BfProbeHandler::handleQueue() {
  // We need to pop a packet from the queue and send it back to this module, making sure that 
  // it will be handled
  EV_INFO << "(BF PROBE HANDLER) Checking if probing process can continue with probes from the queue\n";

  auto& state = getSharedState();
  if (state.queue.size() == 0) {
    EV_INFO << "(BF PROBE HANDLER) Queue is empty\n";
    return true;
  }
  EV_INFO << "(BF PROBE HANDLER) Handling packet from queue\n";
  inet::Packet* queuedPacket = state.queue.front();
  state.queue.pop_front();
  sendPacketLo(queuedPacket);
  return false;
}
    
bool BfProbeHandler::handleProbe() {
  EV_INFO << "(BF PROBE HANDLER) Probing\n";
  auto& state = getSharedState();
  auto& data = packetData.data;

  int size = router->getPortsFunc()
    .filter([this](PredictablePort* port) { 
      return port->getId() != packetData.sourceInterface;
    })
    .mapKeep<Route>([this, state, data](PredictablePort* port) {
      return router->getProbingRoute(port, state.flow.dest, state.params, data->getStats());
    })
    .filter([](const std::pair<PredictablePort*, Route>& pair) {
      return pair.second.isViable();
    })
    .map<Link>([this, data](const std::pair<PredictablePort*, Route>& pair) {
      return router->getAllocationStrategy().chooseQueue(pair.first, data, pair.second);
    })
    .forEach([this, &state, data](Link& link) mutable {
      FlowParameters newParams = link.allocate(state.params);
      sendPacket(
        PacketCreator::createFlowProbePacket(data, newParams, link.getDelay()), 
        link.getInterfaceId()
      );
      state.unconfirmedProbes[link.getInterfaceId()] = link.getQueue();
    })
    .size();

  if (size == 0) {
    EV_INFO << "(BF PROBE HANDLER) Probing failed\n";
    if (!state.isFirstHop) {
      sendPacket(
        PacketCreator::createFlowPrunePacket(state.flow),
        state.interfaceId
      );
      return handleQueue();
    }
    else {
      // We are the starting router and probing failed
      getProtocol()->signalRoutingFailed(state.flow);
    }
    return true;
  }

  getProtocol()->onProbeReservation(state.flow, size);
  return false;
}

}

}