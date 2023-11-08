#ifndef _CRITICAL_TOPLEVELMESSAGEHANDLER_H
#define _CRITICAL_TOPLEVELMESSAGEHANDLER_H

#include "critical/common/handler/base/MessageHandlerBase.h"

namespace critical {

class TopLevelMessageHandler: public MessageHandlerBase {

  public:
    TopLevelMessageHandler(CriticalProtocol* const protocol);
    virtual ~TopLevelMessageHandler();

    void receiveMessage(cMessage* msg);

    virtual uint64_t estimateMemoryFootprint() const = 0;

};

}

#endif 