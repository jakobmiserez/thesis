#include "DfConfirmHandler.h"

#include "critical/protocols/probing/packets/PacketCreator.h"

namespace critical {

namespace probing {

DfConfirmHandler::DfConfirmHandler(StatefulMessageHandler<DfState>* parent)
: SharedStatePacketHandler<FlowConfirmPacket, DfState, ProbingRouter>(parent, PROBE_CONFIRM) {

}

DfConfirmHandler::~DfConfirmHandler() {

}

bool DfConfirmHandler::handleMultiplexedPacket(const inet::Packet* rawPacket) {
  EV_INFO << "Handling flow confirm packet\n";
  preprocessPacket(rawPacket);

  auto& state = getSharedState();
  auto& flowTable = getFlowTable();

  ASSERT(packetData.sourceInterface == state.outgoingInterface);

  // Confirm reroute is faster than failure spread
  if (flowTable.contains(state.flow)) {
    auto [_, entry] = flowTable.deleteFlow(state.flow.src, state.flow.dest, state.flow.label);
    router->getOldFlows().insertFlow(state.flow, entry);
  }

  flowTable.embedFlow(
    state.flow,
    state.params,
    state.outgoingInterface,
    packetData.sourceAddress,
    state.incomingInterface,
    state.queue,
    false,
    state.isFirstHop
  );

  if (state.incomingInterface != pparent->getProtocol()->getLo()->getInterfaceId()) {
    sendPacket(
      PacketCreator::createFlowConfirmPacket(state.flow),
      state.incomingInterface
    );
  }

  return true;
}

}

}


