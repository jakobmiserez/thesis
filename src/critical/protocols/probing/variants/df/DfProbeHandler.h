#ifndef _CRITICAL_DFPROBEHANDLER_H
#define _CRITICAL_DFPROBEHANDLER_H

#include "critical/common/handler/multiplex/PureMultiplexedPacketHandler.h"
#include "critical/common/handler/stateful/SharedStatePacketHandler.h"
#include "critical/protocols/probing/packets/ProbingPackets_m.h"
#include "critical/protocols/probing/variants/df/DfStates.h"
#include "critical/protocols/probing/ProbingRouter.h"

namespace critical {

namespace probing {

class DfProbeHandler
: public SharedStatePacketHandler<FlowProbePacket, DfState, ProbingRouter>,
  public PureMultiplexedPacketHandler {

  public:
    DfProbeHandler(StatefulMessageHandler<DfState>* parent);
    virtual ~DfProbeHandler();

    virtual bool handleMultiplexedPacket(const inet::Packet* rawPacket) override;

  private:
    bool handleAtDestination();
    bool handleProbing();
};

}

}

#endif 