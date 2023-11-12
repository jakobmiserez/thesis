#include "LsLsaHandler.h"

#include "LsTimerTypes.h"
#include "critical/protocols/ls/minimal/MinimalLsRouter.h"
#include "critical/protocols/ls/packets/PacketCreator.h"

namespace critical {

namespace ls {

LsLsaHandler::LsLsaHandler(MessageHandlerBase* parent)
: SingleplexPacketHandlerBase(parent, LS_LSA),
  lsaCollectTimer("LSA collect") {

  pparent->registerTimerHandler(LsTimerType::LSA_TIMER, this);
  pparent->registerTimerHandler(&lsaCollectTimer, this);
}

LsLsaHandler::~LsLsaHandler() {
  pparent->deregisterTimerHandler(LsTimerType::LSA_TIMER, this);
  pparent->deregisterTimerHandler(&lsaCollectTimer, this);
}

void LsLsaHandler::handlePacket(const inet::Packet* const rawPacket) {
  EV_INFO << "(LSA HANDLER) Received LSA\n";
  preprocessPacket(rawPacket);

  auto& packetCreator = router->getPacketCreator();
  auto& lsas = router->getLSAs();
  if (lsas.insertLsa(packetData.data)) {
    EV_INFO << "(LSA HANDLER) I should forward this LSA\n";
    for (const auto& [_, entry]: router->getNeighborTable()) {
      if (entry.interfaceId != packetData.sourceInterface && entry.isFullyAdjacent()) {
        sendPacket(packetCreator.dupLsa(packetData.data), entry.interfaceId, entry.neighborAddress);
      }
    }
  }
  else {
    EV_INFO << "(LSA HANDLER) Ignoring outdated LSA\n";
  }
}

void LsLsaHandler::handleTimer(cMessage* timer) {
  if (timer == &lsaCollectTimer) {
    return handleLsaCollection();
  }
  EV_INFO << "(LSA HANDLER) Sending LSAs\n";
  // Construct LSA packet and send to adjecent routers

  auto& nt = router->getNeighborTable();
  auto& packetCreator = router->getPacketCreator();

  inet::Packet* lsa = packetCreator.createLsa();
  const LsaPacket* data = lsa->peekAtFront<LsaPacket>().get();

  // Insert the router's own lsa such that is in the database
  router->getLSAs().insertLsa(data);

  // If optimize LSAs is false, then we send actual LSAs in order to build the network map.
  // Otherwise, we rely on external simulation tools like the 'LsaOptimizer' to fix this.
  if (!getProtocol()->getParams().optimizeLsas) {
    for (const auto& [_, entry]: nt) {
      if (entry.isFullyAdjacent()) {
        sendPacket(lsa->dup(), entry.interfaceId, entry.neighborAddress);
      }
    }
  }

  delete lsa;

  // Start collection after 2 seconds 
  pparent->startTimer(&lsaCollectTimer, SimTime(2.0, SimTimeUnit::SIMTIME_S));
}

void LsLsaHandler::handleLsaCollection() {
  EV_INFO << "(LSA HANDLER) Rebuilding tables using all LSAs\n";
  router->setUpdatesAutomatically(true);
  router->rebuild();
}

}

}