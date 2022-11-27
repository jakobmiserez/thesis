#include "PacketCreatorBase.h"

#include "critical/CriticalProtocol.h"

#include <inet/common/ProtocolTag_m.h>

namespace critical {

inet::Packet* PacketCreatorBase::wrap(const inet::Ptr<CriticalPacketBase> critical, const std::string message = "Critical Data") {
  inet::Packet* packet = new inet::Packet(message.c_str());
  packet->insertAtFront(critical);
  packet->addTagIfAbsent<inet::PacketProtocolTag>()->setProtocol(&CriticalProtocol::asInetProtocol);
 
  return packet;
}

const std::string PacketCreatorBase::messageWithCounter(const char* const message, Counter& counter) {
  std::string msg(message);
  msg.append(" ");
  msg.append(std::to_string(counter++));
  return msg;
}

}