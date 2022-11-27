#include "PacketDistributor.h"

namespace critical {

PacketDistributor::PacketDistributor(): firstPacket(true) {

}

PacketDistributor::~PacketDistributor() {

}

void PacketDistributor::registerPacketHandler(IPacketHandler* handler, PacketType type) {
  auto it = packetHandlers.find(type);
  if (it != packetHandlers.end()) { 
    throw cRuntimeError("Cannot register a handler for the same packet type (%i)", type);
  }
  packetHandlers[type] = handler;
}

void PacketDistributor::deregisterPacketHandler(IPacketHandler* handler, PacketType type) {
  auto it = packetHandlers.find(type);
  if (it != packetHandlers.end() && it->second == handler) { 
    packetHandlers.erase(type);
  }
}

void PacketDistributor::distributePacket(const inet::Packet* packet, PacketType type) {
  auto it = packetHandlers.find(type);
  if (it != packetHandlers.end()) {
    it->second->handlePacket(packet);
    firstPacket = false;
  }
  else {
    EV_WARN << "No packet handler found for type " << (int)type << "\n";
  }
}

bool PacketDistributor::distributeMultiplexedPacket(const inet::Packet* packet, PacketType type) {
  auto it = packetHandlers.find(type);
  if (it != packetHandlers.end()) {
    bool res = it->second->handleMultiplexedPacket(packet);
    firstPacket = false;
    return res;
  }
  else {
    EV_WARN << "No packet handler found for type " << type << "\n";
    return false;
  }
}

}