#ifndef _CRITICAL_BFPRUNEHANDLER_H
#define _CRITICAL_BFPRUNEHANDLER_H

#include "BfStates.h"
#include "critical/protocols/probing/packets/ProbingPackets_m.h"
#include "critical/protocols/probing/ProbingRouter.h"
#include "critical/common/handler/stateful/SharedStatePacketHandler.h"
#include "critical/common/handler/multiplex/PureMultiplexedPacketHandler.h"

namespace critical {

namespace probing {

class BfPruneHandler : 
  public SharedStatePacketHandler<FlowPrunePacket, BfState, ProbingRouter>,
  public PureMultiplexedPacketHandler {

  public:
    BfPruneHandler(StatefulMessageHandler<BfState>* parent);
    virtual ~BfPruneHandler();

    virtual bool handleMultiplexedPacket(const inet::Packet* const rawPacket) override;

  private:
    bool handleQueue();

    bool handleFastPrune();
};

}

}

#endif 