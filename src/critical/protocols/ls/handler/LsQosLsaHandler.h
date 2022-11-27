#ifndef _CRITICAL_LSQOSLSAHANDLER_H
#define _CRITICAL_LSQOSLSAHANDLER_H

#include "critical/common/handler/singleplex/SingleplexPacketHandlerBase.h"
#include "critical/common/handler/base/TimerHandlerBase.h"
#include "critical/protocols/ls/packets/LsPackets_m.h"
#include "critical/protocols/ls/LsRouter.h"

namespace critical {

namespace ls {

class LsQosLsaHandler: public SingleplexPacketHandlerBase<QosLsaPacket, LsRouter>, public TimerHandlerBase {
  public:
    LsQosLsaHandler(MessageHandlerBase* parent);
    ~LsQosLsaHandler();

    void handlePacket(const inet::Packet* const rawPacket) override;

    virtual void handleTimer(cMessage* timer) override;

    virtual void handleStartTimer(cMessage* startTimer) override;

};

} 
  
} 

#endif 