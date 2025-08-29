#include "BfPruneHandler.h"

#include "critical/protocols/probing/packets/PacketCreator.h"
#include "critical/protocols/probing/ProbingRouter.h"
#include "critical/common/util/Util.h"

#include <inet/networklayer/common/L3AddressResolver.h>

namespace critical {

namespace probing {

BfPruneHandler::BfPruneHandler(StatefulMessageHandler<BfState>* parent)
: SharedStatePacketHandler<FlowPrunePacket, BfState, ProbingRouter>(parent, PROBE_PRUNE) {

}

BfPruneHandler::~BfPruneHandler() {

}

bool BfPruneHandler::handleMultiplexedPacket(const inet::Packet* const rawPacket) {
  preprocessPacket(rawPacket);
  inet::L3AddressResolver resolver;
  EV_INFO << "(BF PRUNE HANDLER) Handling prune packet from " << resolver.findHostWithAddress(packetData.sourceAddress)->getFullPath() << "\n";
  EV_INFO << "(BF PRUNE HANDLER) " << packetData.data->getFlow() << "\n";
  EV_INFO << "(BF PRUNE HANDLER) Prune arrived at port " << packetData.sourceInterface << "\n";

  auto& state = getSharedState();

  if (state.unconfirmedProbes.find(packetData.sourceInterface) == state.unconfirmedProbes.end()) {
    EV_INFO << "(BF PRUNE HANDLER) Received outdated prune, ignoring\n";
    return false;
  }

  if (state.interfaceId == packetData.sourceInterface) {
    return handleFastPrune();
  }

  

  int queue = state.unconfirmedProbes.at(packetData.sourceInterface);
  router->getPortById(packetData.sourceInterface)->freeFlow(queue, state.params);
  state.unconfirmedProbes.erase(packetData.sourceInterface);
  getProtocol()->onProbeReservation(state.flow, -1);

  EV_INFO << "(BF PRUNE HANDLER) Still having " << state.unconfirmedProbes.size() << " unconfirmed probes\n";
  
  if (state.unconfirmedProbes.size() == 0) {
    if (!state.isFirstHop) {
      EV_INFO << "(BF PRUNE HANDLER) Sending prune back\n"; 
      sendPacket(
        PacketCreator::createFlowPrunePacket(state.flow),
        state.interfaceId
      );
      return handleQueue();
    }
    else {
      getProtocol()->signalRoutingFailed(state.flow);
      return true;
    }
  }
  return false;
}

bool BfPruneHandler::handleQueue() {
  auto& state = getSharedState();
  if (state.queue.size() == 0) {
    return true;
  }
  
  EV_INFO << "(BF PRUNE HANDLER) Handling packet from queue\n";

  inet::Packet* queuedPacket = state.queue.front();
  state.queue.pop_front();
  sendPacketLo(queuedPacket);

  return false;
}

bool BfPruneHandler::handleFastPrune() {
  ASSERT(getParams().probingFastPrune);
  EV_INFO << "(BF PRUNE HANDLER) Handling fast prune, pruning upstream\n";

  auto& state = getSharedState();
  for (const auto& [port, queue]: state.unconfirmedProbes) {
    router->getPortById(port)->freeFlow(queue, state.params);
    EV_INFO << "(BF PRUNE HANDLER) Sending upstream prune to " << port << "\n";
    sendPacket(PacketCreator::createFlowPrunePacket(state.flow), port);
  }

  getProtocol()->onProbeReservation(state.flow, -state.unconfirmedProbes.size());
  state.unconfirmedProbes.clear();

  return true;
}

}

}