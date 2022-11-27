#include "LsQosLsaHandler.h"

#include "critical/protocols/ls/LsRouter.h"
#include <inet/networklayer/common/L3AddressResolver.h>


namespace critical {

namespace ls {

LsQosLsaHandler::LsQosLsaHandler(MessageHandlerBase* parent)
: SingleplexPacketHandlerBase(parent, LS_QOS_LSA),
  TimerHandlerBase(parent, "QoSLSA timer") {

}

LsQosLsaHandler::~LsQosLsaHandler() {

}

void LsQosLsaHandler::handlePacket(const inet::Packet* const rawPacket) {
  EV_INFO << "(QOSLSA HANDLER) HANDLING QOS LSA\n";
  preprocessPacket(rawPacket);

  EV_INFO << "From: " << inet::L3AddressResolver().findHostWithAddress(packetData.data->getRouterId())->getFullPath() << "\n";  

  auto& pc = router->getPacketCreator();

  auto& lsas = router->getQosLSAs();
  if (lsas.insertQosLsa(packetData.data)) {
    for (const auto& [id, neighbor]: router->getNeighborTable()) {
      if (id == packetData.sourceInterface || !neighbor.isFullyAdjacent()) {
        continue;
      }
      sendPacket(pc.dupQosLsa(packetData.data), id, neighbor.neighborAddress);
    }
  }
}

void LsQosLsaHandler::handleTimer(cMessage* timer) {
  EV_INFO << "(LS QOS LSA HANDLER) Sending out timed LSAs\n";
  for (const auto& port: router->getPorts()) {
    router->sendOutQosLsa(port.getId());
  }
  tparent->startTimer(timer, getProtocol()->getParams().lsUpdateInterval);
}

void LsQosLsaHandler::handleStartTimer(cMessage* startTimer) {
  const auto& params = getParams();
  if (params.lsUpdateStrategy == LsUpdateStrategy::TIMED && params.lsUpdateInterval > 0) {
    tparent->startTimer(&timer, 5.0 + getProtocol()->dblrand() / 5.0);
  }
}

}

}