#ifndef _CRITICAL_STATELESSMESSAGEHANDLER_H
#define _CRITICAL_STATELESSMESSAGEHANDLER_H

#include "critical/common/handler/base/MessageHandlerBase.h"

namespace critical {

class StatelessMessageHandler: public MessageHandlerBase, public IPacketHandler, public ITimerHandler {
  public:
    StatelessMessageHandler(CriticalProtocol* protocol);
    virtual ~StatelessMessageHandler();

    virtual void handlePacket(const inet::Packet* const rawPacket) override;
    virtual bool handleMultiplexedPacket(const inet::Packet* const rawPacket) override;
    virtual void handleTimer(cMessage* timer) override;
    virtual void handleStartTimer(cMessage* startTimer) override;
};

}

#endif