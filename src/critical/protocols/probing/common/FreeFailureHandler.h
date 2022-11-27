#ifndef _CRITICAL_PROBING_FREEFAILUREHANDLER_H
#define _CRITICAL_PROBING_FREEFAILUREHANDLER_H

#include "critical/common/handler/singleplex/SingleplexPacketHandlerBase.h"
#include "critical/protocols/probing/packets/ProbingPackets_m.h"
#include "critical/protocols/probing/ProbingRouter.h"

namespace critical {

namespace probing {

class FreeFailureHandler: public SingleplexPacketHandlerBase<FlowFreeFailurePacket, ProbingRouter> {
  public:
    FreeFailureHandler(MessageHandlerBase* parent);
    virtual ~FreeFailureHandler();

    virtual void handlePacket(const inet::Packet* const rawPacket);

    FlowTableEntry deleteEntry();

};

}

}


#endif