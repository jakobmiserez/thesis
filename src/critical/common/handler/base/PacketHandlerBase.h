#ifndef _CRITICAL_PACKETHANDLERBASE_H
#define _CRITICAL_PACKETHANDLERBASE_H

#include "critical/common/handler/IHandler.h"
#include "critical/common/handler/base/MessageHandlerBase.h"
#include "critical/common/routing/RouterBase.h"
#include "critical/flows/FlowTable.h"
#include "critical/CriticalProtocol.h"
#include "critical/common/packet/OriginalSourceTag_m.h"

namespace critical {

//template <class T>
//struct packetData

template <class T, class R>
class PacketHandlerBase: public virtual IPacketHandler {
  protected:
    MessageHandlerBase* pparent;
    PacketType packetType;
    R* router;

    struct PacketData {
      inet::L3Address sourceAddress;
      int sourceInterface;
      const T* data;
    };

    PacketHandlerBase::PacketData packetData;

  public:
    PacketHandlerBase(MessageHandlerBase* parent, PacketType type) : pparent(parent), packetType(type) {
      pparent->registerPacketHandler(this, packetType);
      router = check_and_cast<R*>(parent->getProtocol()->getRouter());
    };

    virtual ~PacketHandlerBase() {
      pparent->deregisterPacketHandler(this, packetType);
    };

    void preprocessPacket(const inet::Packet* const rawPacket) {
      packetData.data = getPacketData(rawPacket);

      OriginalSourceTag* tag = rawPacket->findTag<OriginalSourceTag>();
      if (tag != nullptr) {
        packetData.sourceAddress = tag->getOriginalSourceAddress();
        packetData.sourceInterface = tag->getOriginalInterface();
      }
      else {
        packetData.sourceAddress = getSourceAddress(rawPacket);
        packetData.sourceInterface = getInterfaceId(rawPacket);
      }
    };

  protected:
    /**
     * @brief Send a packet through the given interfaceId to the given address. If the address is not specified, 
     * the link-local multicast address will be used.
     * 
     * @param packet 
     * @param interfaceId 
     * @param address 
     */
    void sendPacket(inet::Packet* packet, int interfaceId, inet::L3Address address = inet::Ipv6Address::ALL_NODES_2, double delay = 0) {
      pparent->sendPacket(
        packet, 
        address,
        interfaceId,
        delay
      );
    }

    /**
     * @brief Send a packet back to the node that triggered the handling
     * 
     * @param packet 
     */
    void sendPacketBack(inet::Packet* packet, double delay = 0.0) {
      pparent->sendPacket(
        packet,
        packetData.sourceAddress,
        packetData.sourceInterface,
        delay
      );
    };

    void sendReply(inet::Packet* reply, inet::Packet* request, double delay = 0.0) {
      pparent->sendPacket(
        reply,
        getSourceAddress(request),
        getInterfaceId(request),
        delay
      );
    }

    void sendPacketLo(inet::Packet* packet) {
      pparent->getProtocol()->sendPacketLo(packet);
    }

    bool isFirstPacket() {
      return pparent->isFirstPacket();
    }

    CriticalProtocol* getProtocol() {
      return pparent->getProtocol();
    };

    const T* const getPacketData(const inet::Packet* const rawPacket) const {
      return rawPacket->peekAtFront<T>().get();
    };

    const int getInterfaceId(const inet::Packet* const rawPacket) const {
      return rawPacket->getTag<inet::InterfaceInd>()->getInterfaceId();
    };

    const inet::Ipv6Address getSourceAddress(const inet::Packet* const rawPacket) const {
      auto tag = rawPacket->findTag<inet::L3AddressInd>();
      if (tag == nullptr) {
        return inet::Ipv6Address::LOOPBACK_ADDRESS;
      }
      return tag->getSrcAddress().toIpv6();
    };

    FlowTable& getFlowTable() { return pparent->getProtocol()->getFlowTable(); };

    const CriticalProtocolParameters& getParams() { return pparent->getProtocol()->getParams(); };

};

}

#endif 