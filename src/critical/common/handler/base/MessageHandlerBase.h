#ifndef _CRITICAL_MessageHandlerBase_H
#define _CRITICAL_MessageHandlerBase_H

#include "critical/common/handler/IHandler.h"
#include "critical/common/handler/distributor/PacketDistributor.h"
#include "critical/common/handler/distributor/TimerDistributor.h"
#include "critical/common/util/ProtocolComponent.h"

#include <omnetpp.h>
#include <inet/common/packet/Packet.h>
#include <inet/networklayer/common/InterfaceEntry.h>

using namespace omnetpp;

namespace critical {

class CriticalProtocol;

class MessageHandlerBase: public PacketDistributor, public TimerDistributor, public ProtocolComponent {
  public:
    MessageHandlerBase(CriticalProtocol* const protocol);
    virtual ~MessageHandlerBase();

    void startTimer(cMessage* timer, simtime_t delay);
    void clearTimer(cMessage* timer);

    void sendPacket(inet::Packet* packet, const inet::L3Address& address, const inet::InterfaceEntry* interface, double delay = 0);
    void sendPacket(inet::Packet* packet, const inet::L3Address& address, int interfaceId, double delay = 0);

    CriticalProtocol* getProtocol() { return protocol; };

    protected:
      PacketType extractPacketType(const inet::Packet* packet);

      void handleTimer(cMessage* msg);
      void handlePacket(inet::Packet* packet);

};

}

#endif