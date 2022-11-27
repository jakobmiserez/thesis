#ifndef _CRITICAL_LS_PACKETCREATOR_H
#define _CRITICAL_LS_PACKETCREATOR_H

#include "critical/protocols/ls/packets/LsPackets_m.h"
#include "critical/common/packet/PacketCreatorBase.h"
#include "critical/flows/Flow.h"
#include "critical/protocols/ls/topology/Topology.h"

#include <map>

namespace critical {

namespace ls {

class MinimalLsRouter;

class PacketCreator: public PacketCreatorBase {
  private:
    MinimalLsRouter* router;
    uint32_t lsaSequenceNumber;
    std::map<int, uint32_t> nextQosSequenceNumbers;

  public:
    PacketCreator(MinimalLsRouter* router);
    ~PacketCreator();

    inet::Packet* createHelloPacket();
    inet::Packet* createLsa();
    inet::Packet* dupLsa(const LsaPacket* lsaPacket);
    inet::Packet* createQosLsa(int interfaceId);
    inet::Packet* dupQosLsa(const QosLsaPacket* qosLsaPacket);
    inet::Packet* createEmbedPacket(const Flow& flow, const std::vector<const Topology::Link*>& path);
    inet::Packet* updateEmbedPacket(const LsEmbedPacket* flowEmbedPacket, const FlowParameters& updatedParams);
    inet::Packet* createEmbedConfirmPacket(const FlowId& flow);
    inet::Packet* createEmbedFailPacket(const FlowId& flow);

  private:
    uint32_t getNextLsaSequenceNumber();
    uint32_t getNextLsaQosSequenceNumber(int interfaceId);
};

}

}


#endif 