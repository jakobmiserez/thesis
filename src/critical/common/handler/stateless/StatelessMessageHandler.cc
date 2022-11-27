#include "StatelessMessageHandler.h"

namespace critical {

StatelessMessageHandler::StatelessMessageHandler(CriticalProtocol* protocol)
: MessageHandlerBase(protocol) {

}

StatelessMessageHandler::~StatelessMessageHandler() {

}

void StatelessMessageHandler::handlePacket(const inet::Packet* const rawPacket) {
  distributePacket(rawPacket, extractPacketType(rawPacket));
}

bool StatelessMessageHandler::handleMultiplexedPacket(const inet::Packet* const rawPacket) {
  return distributeMultiplexedPacket(rawPacket, extractPacketType(rawPacket));
}

void StatelessMessageHandler::handleTimer(cMessage* timer) {
  distributeTimer(timer);  
}
    
void StatelessMessageHandler::handleStartTimer(cMessage* startTimer) {
  distributeStartTimer(startTimer);
}

}