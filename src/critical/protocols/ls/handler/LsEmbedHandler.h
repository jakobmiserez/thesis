#ifndef _CRITICAL_LSEMBEDHANDLER_H
#define _CRITICAL_LSEMBEDHANDLER_H

#include "critical/common/handler/singleplex/SingleplexPacketHandlerBase.h"
#include "critical/protocols/ls/packets/LsPackets_m.h"
#include "critical/protocols/ls/LsRouter.h"

namespace critical {

namespace ls {

class LsEmbedHandler: public SingleplexPacketHandlerBase<LsEmbedPacket, LsRouter> {
  public:
    LsEmbedHandler(MessageHandlerBase* parent);
    ~LsEmbedHandler();

    virtual void handlePacket(const inet::Packet* const rawPacket) override;
};

}

}



#endif 