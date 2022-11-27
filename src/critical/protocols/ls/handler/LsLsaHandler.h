#ifndef _CRITICAL_LS_LSAHANDLER_H
#define _CRITICAL_LS_LSAHANDLER_H

#include "critical/common/handler/IHandler.h"
#include "critical/protocols/ls/packets/LsPackets_m.h"
#include "critical/common/handler/singleplex/SingleplexPacketHandlerBase.h"
#include "critical/protocols/ls/minimal/MinimalLsRouter.h"

namespace critical {

namespace ls {

class LsLsaHandler: public SingleplexPacketHandlerBase<LsaPacket, MinimalLsRouter>, public ITimerHandler {
  public:
    cMessage lsaCollectTimer;

    LsLsaHandler(MessageHandlerBase* parent);
    virtual ~LsLsaHandler();

    virtual void handlePacket(const inet::Packet* const rawPacket) override;
    virtual void handleTimer(cMessage* timer) override;
    virtual void handleStartTimer(cMessage* startTimer) override {};

  private:
    void handleLsaCollection();


};

}

}




#endif 