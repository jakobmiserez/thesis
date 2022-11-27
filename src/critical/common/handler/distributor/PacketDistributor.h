#ifndef _CRITICAL_PACKETDISTRIBUTOR_H
#define _CRITICAL_PACKETDISTRIBUTOR_H

#include "critical/common/handler/IHandler.h"
#include "critical/common/packet/CriticalPacketBase_m.h"

#include <inet/common/packet/Packet.h>

namespace critical {

class PacketDistributor {
  protected:
    std::map<PacketType, IPacketHandler*> packetHandlers;
    bool firstPacket;

  public:
    PacketDistributor();
    virtual ~PacketDistributor();

    void registerPacketHandler(IPacketHandler* handler, PacketType type);
    void deregisterPacketHandler(IPacketHandler* handler, PacketType type);

    void distributePacket(const inet::Packet* packet, PacketType type);
    bool distributeMultiplexedPacket(const inet::Packet* packet, PacketType type);

    bool isFirstPacket() { return firstPacket; }

};

}

#endif 