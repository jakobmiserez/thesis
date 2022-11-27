#ifndef _CRITICAL_LS_HELLOHANDLER_H
#define _CRITICAL_LS_HELLOHANDLER_H

#include "critical/common/handler/singleplex/SingleplexPacketHandlerBase.h"
#include "critical/common/handler/base/TimerHandlerBase.h"
#include "critical/common/handler/IHandler.h"
#include "critical/protocols/ls/minimal/MinimalLsRouter.h"
#include "critical/protocols/ls/packets/LsPackets_m.h"

namespace critical {

namespace ls {

class LsHelloHandler: public SingleplexPacketHandlerBase<LsHelloPacket, MinimalLsRouter>, public ITimerHandler {   
  private:
    cMessage helloTimer;
    cMessage initialLsaTimer;

  public:
    LsHelloHandler(MessageHandlerBase* parent);
    virtual ~LsHelloHandler();

    virtual void handlePacket(const inet::Packet* const rawPacket) override;
    virtual void handleTimer(cMessage* timer) override;
    virtual void handleStartTimer(cMessage* startTimer) override;

  private:
    void sendHelloPackets();
};

}

}


#endif 