#include "LsHelloHandler.h"

#include "critical/protocols/ls/handler/LsTimerTypes.h"
#include "critical/protocols/ls/packets/PacketCreator.h"
#include "critical/protocols/ls/minimal/MinimalLsRouter.h"
#include "inet/networklayer/ipv6/Ipv6InterfaceData.h"
#include "critical/common/util/Util.h"
#include "LsTimerTypes.h"

namespace critical {

namespace ls {

LsHelloHandler::LsHelloHandler(MessageHandlerBase* parent)
: SingleplexPacketHandlerBase(parent, LS_HELLO),
  helloTimer("hello", LsTimerType::HELLO_TIMER),
  initialLsaTimer("lsa", LsTimerType::LSA_TIMER) {

  pparent->registerTimerHandler(&helloTimer, this);
}

LsHelloHandler::~LsHelloHandler() {
  pparent->deregisterTimerHandler(&helloTimer, this);
}

void LsHelloHandler::handlePacket(const inet::Packet* const rawPacket) {
  EV_INFO << "(HELLO HANDLER) Handling hello packet\n";
  preprocessPacket(rawPacket);

  auto& neighbors = router->getNeighborTable();

  neighbors.setNeighborInfo(
    packetData.sourceInterface, 
    packetData.data->getRouterId(),
    packetData.sourceAddress.toIpv6()
  ); 
}

void LsHelloHandler::handleTimer(cMessage* timer) {

}

void LsHelloHandler::handleStartTimer(cMessage* startTimer) {
  sendHelloPackets();

  // Start the initial lsa timer after 1s 
  pparent->startTimer(&initialLsaTimer, SimTime(1.0, SimTimeUnit::SIMTIME_S));
}

void LsHelloHandler::sendHelloPackets() {
  EV_INFO << "(HELLO HANDLER) Sending hello packets\n";  
  auto& packetCreator = router->getPacketCreator();

  for (auto& interface: router->getInterfaces()) {
    int id = interface->getInterfaceId();
    sendPacket(packetCreator.createHelloPacket(), id);

    router->getNeighborTable().sentHello(id);
  }
}

}

}