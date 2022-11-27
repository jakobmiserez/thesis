#ifndef _CRITICAL_HELPERS_H
#define _CRITICAL_HELPERS_H

#include "critical/CriticalProtocol.h"
#include "critical/flows/Flow.h"
#include "critical/protocols/probing/packets/ProbingPackets_m.h"

#include <inet/common/packet/Packet.h>
#include <set>

namespace critical {

namespace probing {

inline const FlowId& extractFlowFromProbingPacket(const inet::Packet* const packet) {
  return packet->peekAtFront<ProbingPacketBase>()->getFlow();
};

inline PacketType extractFlowPacketType(const inet::Packet* const packet) {
  return packet->peekAtFront<ProbingPacketBase>()->getType();
};

}

}


#endif 