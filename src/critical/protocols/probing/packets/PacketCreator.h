#ifndef __PACKETCREATOR_H__
#define __PACKETCREATOR_H__

#include "critical/common/packet/PacketCreatorBase.h"
#include "critical/flows/Flow.h"
#include "critical/protocols/probing/packets/ProbingPackets_m.h"

namespace critical {

namespace probing {

class PacketCreator : public PacketCreatorBase {
  public:
    static inet::Packet* createFlowProbePacket(
      const FlowProbePacket* previousProbe,
      const FlowParameters& newParams,
      uint64_t delayToAdd
    );
    static inet::Packet* createInitialFlowProbePacket(
      inet::Ipv6Address source,
      inet::Ipv6Address destination,
      uint32_t label,
      uint64_t burst,
      uint64_t bandwidth,
      uint64_t delay,
      uint32_t totalHopEstimate
    );
    static inet::Packet* createFlowPrunePacket(const FlowId& flow);
    static inet::Packet* createFlowFreePacket(const FlowId& flow);
    static inet::Packet* createFlowFreeFailurePacket(const FlowId& id);
    static inet::Packet* createFlowConfirmPacket(const FlowId& flow);

  private:
    static inet::Packet* createFlowProbePacket(
      const FlowId& flow,
      const FlowParameters& params,
      FlowProbeStats stats
    );

};

}

}


#endif // __PACKETCREATOR_H__