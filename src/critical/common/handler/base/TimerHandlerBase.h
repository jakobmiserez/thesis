#ifndef _CRITICAL_TIMERHANDLERBASE_H
#define _CRITICAL_TIMERHANDLERBASE_H

#include "critical/common/handler/IHandler.h"
#include "MessageHandlerBase.h"

namespace critical {

class TimerHandlerBase: public ITimerHandler {
  protected:
    MessageHandlerBase* tparent;
    cMessage timer;

  public:
    TimerHandlerBase(MessageHandlerBase* parent, const char* name): tparent(parent) {
      tparent->registerTimerHandler(&timer, this);
    };

    virtual ~TimerHandlerBase() {
      tparent->clearTimer(&timer);
      tparent->deregisterTimerHandler(&timer, this);
    };
};

}

#endif 