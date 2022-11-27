#ifndef _CRITICAL_LSEMBEDCONFIRMHANDLER_H
#define _CRITICAL_LSEMBEDCONFIRMHANDLER_H

#include "critical/common/handler/singleplex/SingleplexPacketHandlerBase.h"
#include "critical/protocols/ls/packets/LsPackets_m.h"
#include "critical/protocols/ls/LsRouter.h"

namespace critical {

namespace ls {

class LsEmbedConfirmHandler: public SingleplexPacketHandlerBase<LsEmbedConfirmPacket, LsRouter> {
  public:
    LsEmbedConfirmHandler(MessageHandlerBase* parent);
    ~LsEmbedConfirmHandler();

    virtual void handlePacket(const inet::Packet* const rawPacket) override;
};

}

}



#endif 