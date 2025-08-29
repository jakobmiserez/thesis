#include "LsEmbedConfirmHandler.h"

namespace critical {

namespace ls {

LsEmbedConfirmHandler::LsEmbedConfirmHandler(MessageHandlerBase* parent)
: SingleplexPacketHandlerBase(parent, LS_EMBED_CONFIRM) {

}

LsEmbedConfirmHandler::~LsEmbedConfirmHandler() {

}

void LsEmbedConfirmHandler::handlePacket(const inet::Packet* const rawPacket) {
  preprocessPacket(rawPacket);

  const FlowId& flow = packetData.data->getFlow();
  const auto entry = getFlowTable().confirm(flow);

  if (!entry->data.firstHop) {
    sendPacket(
      router->getPacketCreator().createEmbedConfirmPacket(flow), entry->data.prevInterface
    );
  }
  else {
    getProtocol()->tries += router->getTriesTable().lookupFlow(flow)->data;
    router->getTriesTable().deleteFlow(flow);
  }
}

}


}