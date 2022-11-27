#ifndef _CRITICAL_IHANDLER_H
#define _CRITICAL_IHANDLER_H

#include <omnetpp.h>
#include <inet/common/packet/Packet.h>
#include <inet/linklayer/common/InterfaceTag_m.h>
#include <inet/networklayer/common/L3AddressTag_m.h>

using namespace omnetpp;

//typedef uint8_t PacketType;
typedef uint8_t TimerType;

class IPacketHandler {
  public:
    virtual ~IPacketHandler() {};
    
    /**
     * @brief Handle a packet once it comes in
     * 
     * @param rawPacket 
     */
    virtual void handlePacket(const inet::Packet* const rawPacket) = 0;

    /**
     * @brief Handle a packet in a multiplexed way. 
     * 
     * @param rawPacket 
     * @return true If the handler 
     * @return false 
     */
    virtual bool handleMultiplexedPacket(const inet::Packet* const rawPacket) = 0;
};

class ITimerHandler {
  public:
    virtual void handleTimer(cMessage* timer) = 0;

    /**
     * @brief Handle the starting timer
     * 
     * @param startTimer 
     */
    virtual void handleStartTimer(cMessage* startTimer) = 0;
};

#endif 