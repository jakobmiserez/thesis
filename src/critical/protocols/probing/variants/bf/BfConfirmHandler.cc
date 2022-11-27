#include "BfConfirmHandler.h"

#include "critical/CriticalProtocol.h"
#include "critical/protocols/probing/ProbingRouter.h"
#include "critical/protocols/probing/packets/PacketCreator.h"

namespace critical {

namespace probing {

BfConfirmHandler::BfConfirmHandler(StatefulMessageHandler<BfState>* parent): 
  SharedStatePacketHandler<FlowConfirmPacket, BfState, ProbingRouter>(parent, PROBE_CONFIRM) {

}

BfConfirmHandler::~BfConfirmHandler() {

}

bool BfConfirmHandler::handleMultiplexedPacket(const inet::Packet* const rawPacket) {
  EV_INFO << "Handling flow confirm packet\n";
  preprocessPacket(rawPacket);
  EV_INFO << packetData.data->getFlow() << "\n";

  FlowTable& flowTable = getFlowTable();
  BfState& state = getSharedState();

  int queue = state.unconfirmedProbes.at(packetData.sourceInterface);

  flowTable.embedFlow(
    state.flow,
    state.params,
    packetData.sourceInterface,
    packetData.sourceAddress,
    state.interfaceId,
    queue,
    false,
    state.isFirstHop
  );

  if (!state.isFirstHop) {
    // Send confirmation back
    sendPacket(
      PacketCreator::createFlowConfirmPacket(state.flow), 
      state.interfaceId
    );
  }

  // Clear waiting packets
  EV_INFO << "Clearing packet queue of " << state.queue.size() << " packets\n";
  for (auto queuedPacket: state.queue) {
    sendReply(PacketCreator::createFlowPrunePacket(state.flow), queuedPacket);
    delete queuedPacket;
  }
  state.queue.clear();

  // Clear allocated flows
  state.unconfirmedProbes.erase(packetData.sourceInterface);
  EV_INFO << "Clearing " << state.unconfirmedProbes.size() << " allocated flows\n";
  for (auto& [port, queue]: state.unconfirmedProbes) {
    router->getPortById(port)->freeFlow(queue, state.params);
    if (getParams().probingFastPrune) {
      sendPacket(PacketCreator::createFlowPrunePacket(state.flow), port);
    }
  }
  state.unconfirmedProbes.clear();

  return true;
}

}

}