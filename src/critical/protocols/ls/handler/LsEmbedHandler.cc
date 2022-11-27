#include "LsEmbedHandler.h"
#include "critical/protocols/ls/LsRouter.h"

namespace critical {

namespace ls {

LsEmbedHandler::LsEmbedHandler(MessageHandlerBase* parent)
: SingleplexPacketHandlerBase<LsEmbedPacket, LsRouter>(parent, LS_EMBED) {

}

LsEmbedHandler::~LsEmbedHandler() {

}

void LsEmbedHandler::handlePacket(const inet::Packet* const rawPacket) {
  EV_INFO << "(LS EMBED HANDLER) Handling embed packet\n";
  preprocessPacket(rawPacket);

  auto& ft = getFlowTable();
  const auto& data = packetData.data;
  const auto& nt = router->getNeighborTable();

  const Flow& flow = data->getFlow();
  bool isFirstHop = data->getHop() == 0;
  bool isFinalHop = data->getHop() == data->getPathArraySize() - 1;
  const auto& [link, queue] = data->getPath(data->getHop());
  inet::Ipv6Address nextHop = nt.getNeighbor(link).neighborAddress;

  // New embedding before old was cleared, can happen on link failure
  if (ft.contains(flow.id)) {
    EV_INFO << "here\n";
    auto entry = ft.deleteFlow(flow.id.src, flow.id.dest, flow.id.label);
    router->getPortById(entry.data.nextInterface)->freeFlow(entry.data.queueNumber, entry.data.params);
    router->getSecondaryPathTable().removePath(flow.id);
    return;
  }



  auto accessControl = router->getPortById(link);
  if (!accessControl->canAllocateFlow(queue, flow.params)) {
    // A collision happened due to inaccuracies or concurrency

    if (isFirstHop) {
      // A collision at the first hop should never happen, as the first hop has a perfect overview of itself
      throw cRuntimeError("Collisions at the first hop should not happen");
    }

    // Add a collision, but send out an LSA to improve accuracy
    getProtocol()->collisions++;
    ASSERT(accessControl->check());
    EV_INFO << "(LS EMBED HANDLER) Collision, sending out QoSLSAs\n";
    router->sendOutQosLsa(link);


    sendPacketBack(router->getPacketCreator().createEmbedFailPacket(flow.id));
    return;
  }
  
  FlowParameters updated = accessControl->allocateFlow(queue, flow.params);

  ft.embedFlow(
    flow.id,
    flow.params,
    link,
    nextHop,
    packetData.sourceInterface,
    queue,
    isFinalHop,
    isFirstHop,
    isFinalHop
  );

  if (!isFirstHop) {
    EV_INFO << "(LS EMBED HANDLER) Saving path in secondary path table\n";
    auto path = router->getQueueLevelTopology().reconstructPath(packetData.data);
    router->getSecondaryPathTable().insertPath(flow, path);
  }
  else {
    auto entry = router->getTriesTable().insertIfAbsent(flow.id, 0);
    entry->data++;
  }

  // Embed further down the path

  if (!isFinalHop) {
    EV_INFO << "(LS EMBED HANDLER) Sending embed packet further down the path\n";
    inet::Packet* nextPacket = router->getPacketCreator().updateEmbedPacket(packetData.data, updated);
    sendPacket(nextPacket, link, nextHop);
  }
  else {
    sendPacketBack(router->getPacketCreator().createEmbedConfirmPacket(flow.id));
  }
}

}

}