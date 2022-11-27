#include "TopLevelMessageHandler.h"

#include "critical/CriticalProtocol.h"

#include <inet/common/ProtocolTag_m.h>

namespace critical {

TopLevelMessageHandler::TopLevelMessageHandler(CriticalProtocol* const protocol) 
  : MessageHandlerBase(protocol) {

};

TopLevelMessageHandler::~TopLevelMessageHandler() {

};

void TopLevelMessageHandler::receiveMessage(cMessage* msg) {
  inet::Packet* packet = dynamic_cast<inet::Packet*>(msg);
  if (packet == nullptr && msg->isSelfMessage()) {
    handleTimer(msg);
  }
  else {
    const inet::Protocol* protocol = packet->getTag<inet::PacketProtocolTag>()->getProtocol();
    
    if (protocol == &CriticalProtocol::asInetProtocol) {
      EV_INFO << "(TOPLEVEL MESSAGE HANDLER) Handling critical protocol packet\n";
      handlePacket(packet);
    }
    else {
      EV_WARN << "(TOPLEVEL MESSAGE HANDLER) Dropping invalid packet\n";
    }
    
    // Delete the packet after it has been handled
    delete packet;
  }
}

}

