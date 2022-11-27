#include "MessageHandlerBase.h"

#include "critical/CriticalProtocol.h"

#include <omnetpp.h>
#include <inet/common/ProtocolTag_m.h>
#include <inet/linklayer/common/InterfaceTag_m.h>
#include <inet/networklayer/common/HopLimitTag_m.h>
#include <inet/networklayer/common/L3AddressTag_m.h>

using namespace omnetpp;


namespace critical {

MessageHandlerBase::MessageHandlerBase(CriticalProtocol* const protocol) 
: ProtocolComponent(protocol) {

}

MessageHandlerBase::~MessageHandlerBase() {
    
}

void MessageHandlerBase::startTimer(cMessage* timer, simtime_t delay) {
  protocol->scheduleAt(simTime() + delay, timer);
}

void MessageHandlerBase::clearTimer(cMessage* timer) {
  protocol->cancelEvent(timer);
}

void MessageHandlerBase::handleTimer(cMessage* msg) {
  if (msg == protocol->getRouter()->getStartTimer()) {
    distributeStartTimer(msg);
  }
  else {
    distributeTimer(msg);
  }
}

void MessageHandlerBase::handlePacket(inet::Packet* packet) {
  PacketType type = extractPacketType(packet);
  distributePacket(packet, type);
}

PacketType MessageHandlerBase::extractPacketType(const inet::Packet* packet) {
  return packet->peekAtFront<CriticalPacketBase>()->getType();
}

void MessageHandlerBase::sendPacket(inet::Packet* packet, const inet::L3Address& address, const inet::InterfaceEntry* interface, double delay) {
  packet->addTagIfAbsent<inet::InterfaceReq>()->setInterfaceId(interface->getInterfaceId());
  packet->addTagIfAbsent<inet::L3AddressReq>()->setSrcAddress(interface->getNetworkAddress());
  packet->addTagIfAbsent<inet::L3AddressReq>()->setDestAddress(address); 
  packet->addTagIfAbsent<inet::DispatchProtocolReq>()->setProtocol(&inet::Protocol::ipv6);
  
  if (delay > 0)
    protocol->sendPacketDelayed(packet, delay);
  else
    protocol->sendPacket(packet);
}

void MessageHandlerBase::sendPacket(inet::Packet* packet, const inet::L3Address& address, int interfaceId, double delay) {
  sendPacket(packet, address, protocol->getRouter()->getInterfaceById(interfaceId), delay);
}

}