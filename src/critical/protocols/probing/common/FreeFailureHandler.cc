#include "FreeFailureHandler.h"

#include "critical/protocols/probing/packets/PacketCreator.h"

namespace critical {

namespace probing {

FreeFailureHandler::FreeFailureHandler(MessageHandlerBase* parent)
: SingleplexPacketHandlerBase(parent, PacketType::PROBE_FREE_FAILURE) {

}

FreeFailureHandler::~FreeFailureHandler() {

}

void FreeFailureHandler::handlePacket(const inet::Packet* const rawPacket) {
  EV_INFO << "(PROBING FREE FAILURE HANDLER) Handling free failure packet\n";
  preprocessPacket(rawPacket);

  auto [flow, entry] = deleteEntry();
  router->getPortById(entry.nextInterface)->freeFlow(entry.queueNumber, entry.params);

  if (packetData.sourceInterface == entry.prevInterface) {
    // Upstream

    if (!entry.finalHop) {
      sendPacket(
        PacketCreator::createFlowFreeFailurePacket(flow), 
        entry.nextInterface
      );
    }
  }
  else if (packetData.sourceInterface == entry.nextInterface) {
    // Downstream
    
    if (!entry.firstHop) {
      sendPacket(
        PacketCreator::createFlowFreeFailurePacket(flow), 
        entry.prevInterface
      );
    }
    else {
      router->reroute(flow, entry.params);
    }
  }
  else {
    throw cRuntimeError("Packet came through unexpected interface");
  }
}

FlowTableEntry FreeFailureHandler::deleteEntry() {
  const FlowId& flow = packetData.data->getFlow();
  if (router->getOldFlows().contains(flow)) {
    return router->getOldFlows().deleteFlow(flow);
  }
  getProtocol()->onProbeReservation(flow, -1);
  return getFlowTable().deleteFlow(flow.src, flow.dest, flow.label);
}

}

}