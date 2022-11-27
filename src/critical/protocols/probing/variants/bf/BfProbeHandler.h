#ifndef _CRITICAL_BFPROBEHANDLER_H
#define _CRITICAL_BFPROBEHANDLER_H

#include "critical/common/handler/stateful/SharedStatePacketHandler.h"
#include "critical/common/handler/multiplex/PureMultiplexedPacketHandler.h"
#include "critical/protocols/probing/packets/ProbingPackets_m.h"
#include "critical/protocols/probing/ProbingRouter.h"
#include "critical/queueing/Link.h"
#include "BfStates.h"

namespace critical {

namespace probing {
  

class BfProbeHandler: 
  public SharedStatePacketHandler<FlowProbePacket, BfState, ProbingRouter>,
  public PureMultiplexedPacketHandler {

  public:
    BfProbeHandler(StatefulMessageHandler<BfState>* parent);
    virtual ~BfProbeHandler();

    virtual bool handleMultiplexedPacket(const inet::Packet* const rawPacket) override;

  private:
    void setParams(const FlowProbePacket* packet);
    bool handleAtDestination();
    bool handleLate();
    bool handleQueue();
    bool handleProbe();
};

}

}


#endif 