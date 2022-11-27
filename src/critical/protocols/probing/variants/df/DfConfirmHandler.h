#ifndef _CRITICAL_DFCONFIRMHANDLER_H
#define _CRITICAL_DFCONFIRMHANDLER_H

#include "critical/common/handler/multiplex/PureMultiplexedPacketHandler.h"
#include "critical/common/handler/stateful/SharedStatePacketHandler.h"
#include "critical/protocols/probing/packets/ProbingPackets_m.h"
#include "critical/protocols/probing/variants/df/DfStates.h"
#include "critical/protocols/probing/ProbingRouter.h"

namespace critical {

namespace probing {

class DfConfirmHandler
: public SharedStatePacketHandler<FlowConfirmPacket, DfState, ProbingRouter>,
  public PureMultiplexedPacketHandler {

  public:
    DfConfirmHandler(StatefulMessageHandler<DfState>* parent);
    virtual ~DfConfirmHandler();

    virtual bool handleMultiplexedPacket(const inet::Packet* rawPacket) override;
};

}

}

#endif 