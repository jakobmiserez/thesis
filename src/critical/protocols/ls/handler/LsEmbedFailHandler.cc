#include "LsEmbedFailHandler.h"

namespace critical {

namespace ls {

LsEmbedFailHandler::LsEmbedFailHandler(MessageHandlerBase* parent)
: SingleplexPacketHandlerBase(parent, LS_EMBED_FAIL) {

}

LsEmbedFailHandler::~LsEmbedFailHandler() {

}

void LsEmbedFailHandler::handlePacket(const inet::Packet* const rawPacket) {
  preprocessPacket(rawPacket);

  const FlowId& flow = packetData.data->getFlow();
  auto entry = getFlowTable().deleteFlow(flow.src, flow.dest, flow.label);

  router->getPortById(entry.data.nextInterface)->freeFlow(entry.data.queueNumber, entry.data.params);

  if (!entry.data.firstHop) {
    router->getSecondaryPathTable().removePath(flow);
    sendPacket(router->getPacketCreator().createEmbedFailPacket(flow), entry.data.prevInterface);
  }
  else {
    router->getPrimaryPathTable().removePath(flow);

    if (router->getTriesTable().lookupFlow(flow)->data < 5) 
      router->startRouting(flow.src, flow.dest, flow.label, entry.data.params.delay, entry.data.params.rate, entry.data.params.burst);
    else {
      router->getTriesTable().deleteFlow(flow);
      getProtocol()->signalRoutingFailed(flow);
      getProtocol()->inaccuracyFails++;
    }
  }
}

}

}