#ifndef _CRITICAL_DFPRUNEHANDLER_H
#define _CRITICAL_DFPRUNEHANDLER_H

#include "critical/common/handler/multiplex/PureMultiplexedPacketHandler.h"
#include "critical/common/handler/stateful/SharedStatePacketHandler.h"
#include "critical/protocols/probing/packets/ProbingPackets_m.h"
#include "critical/protocols/probing/variants/df/DfStates.h"
#include "critical/protocols/probing/ProbingRouter.h"

namespace critical {

namespace probing {

class DfPruneHandler
: public SharedStatePacketHandler<FlowPrunePacket, DfState, ProbingRouter>,
  public PureMultiplexedPacketHandler {

  public:
    DfPruneHandler(StatefulMessageHandler<DfState>* parent);
    virtual ~DfPruneHandler();

    virtual bool handleMultiplexedPacket(const inet::Packet* rawPacket) override;
};

}

}

#endif 