#ifndef _CRITICAL_BFCONFIRMHANDLER_H
#define _CRITICAL_BFCONFIRMHANDLER_H

#include "BfStates.h"
#include "critical/protocols/probing/packets/ProbingPackets_m.h"
#include "critical/common/handler/stateful/SharedStatePacketHandler.h"
#include "critical/common/handler/multiplex/PureMultiplexedPacketHandler.h"
#include "critical/protocols/probing/ProbingRouter.h"

namespace critical {

namespace probing {

class BfConfirmHandler
: public SharedStatePacketHandler<FlowConfirmPacket, BfState, ProbingRouter>,
  public PureMultiplexedPacketHandler {

  public:
    BfConfirmHandler(StatefulMessageHandler<BfState>* parent);
    ~BfConfirmHandler();

    virtual bool handleMultiplexedPacket(const inet::Packet* const rawPacket) override;
};

}

}

#endif