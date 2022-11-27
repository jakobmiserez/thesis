#ifndef _CRITICAL_STATEFULPACKETHANDLER_H
#define _CRITICAL_STATEFULPACKETHANDLER_H

#include "critical/common/handler/IHandler.h"
#include "critical/common/handler/distributor/PacketDistributor.h"
#include "critical/common/handler/base/MessageHandlerBase.h"
#include "critical/common/handler/stateless/StatelessMessageHandler.h"

namespace critical {

template <class T>
class StatefulMessageHandler: public StatelessMessageHandler {
  protected:
    T state;

  public:
    StatefulMessageHandler(CriticalProtocol* const protocol, T initialState);
    virtual ~StatefulMessageHandler();

    T& getSharedState() { return state; };
};

}

#include "StatefulMessageHandler.tcc"

#endif 