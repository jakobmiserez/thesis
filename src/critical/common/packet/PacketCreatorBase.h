#ifndef _CRITICAL_PacketCreatorBase_H
#define _CRITICAL_PacketCreatorBase_H

#include "critical/common/packet/CriticalPacketBase_m.h"

#include <inet/common/packet/Packet.h>
#include <inet/networklayer/contract/ipv6/Ipv6Address.h>

namespace critical {

class PacketCreatorBase {
  protected:
    typedef uint64_t Counter;

    static inet::Packet* wrap(const inet::Ptr<CriticalPacketBase> critical, const std::string message);
    static const std::string messageWithCounter(const char* const message, Counter& counter);

};

}

#endif