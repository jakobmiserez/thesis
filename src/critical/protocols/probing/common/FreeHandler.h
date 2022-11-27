#ifndef _CRITICAL_BFFREEHANDLER_H
#define _CRITICAL_BFFREEHANDLER_H

#include "critical/common/handler/singleplex/SingleplexPacketHandlerBase.h"
#include "critical/protocols/probing/packets/ProbingPackets_m.h"
#include "critical/protocols/probing/ProbingRouter.h"

namespace critical {

namespace probing {

class FreeHandler: public SingleplexPacketHandlerBase<FlowFreePacket, ProbingRouter> {
  public:
    FreeHandler(MessageHandlerBase* parent);
    virtual ~FreeHandler();

    virtual void handlePacket(const inet::Packet* const rawPacket) override;
};

}

}

#endif 