#ifndef _CRITICAL_LSEMBEDFAILHANDLER_H
#define _CRITICAL_LSEMBEDFAILHANDLER_H

#include "critical/common/handler/singleplex/SingleplexPacketHandlerBase.h"
#include "critical/protocols/ls/packets/LsPackets_m.h"
#include "critical/protocols/ls/LsRouter.h"

namespace critical {

namespace ls {

class LsEmbedFailHandler: public SingleplexPacketHandlerBase<LsEmbedFailPacket, LsRouter> {
  public:
    LsEmbedFailHandler(MessageHandlerBase* parent);
    ~LsEmbedFailHandler();

    virtual void handlePacket(const inet::Packet* const rawPacket) override;
};

}

}



#endif 