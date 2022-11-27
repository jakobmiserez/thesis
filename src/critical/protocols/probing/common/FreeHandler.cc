#include "FreeHandler.h"

#include "critical/protocols/probing/packets/PacketCreator.h"

namespace critical {

namespace probing {

FreeHandler::FreeHandler(MessageHandlerBase* parent)
: SingleplexPacketHandlerBase<FlowFreePacket, ProbingRouter>(parent, PROBE_FREE) {

}
  
FreeHandler::~FreeHandler() {

}

void FreeHandler::handlePacket(const inet::Packet* const rawPacket) {
  EV_INFO << "Handling a flow free packet\n";
  auto& flowTable = getFlowTable();
  auto data = getPacketData(rawPacket);

  auto entry = flowTable.deleteFlow(data->getFlow().src, data->getFlow().dest, data->getFlow().label);

  if (!entry.data.finalHop) {
    sendPacket(
      PacketCreator::createFlowFreePacket(data->getFlow()),
      entry.data.nextInterface,
      entry.data.nextHop
    );
  }
}

}

}