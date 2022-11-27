#ifndef _CRITICAL_TIMERDISTRIBUTORBASE_H
#define _CRITICAL_TIMERDISTRIBUTORBASE_H

#include "critical/common/handler/IHandler.h"

namespace critical {

class TimerDistributor {
  protected:
    std::map<cMessage*, ITimerHandler*> timerHandlers;
    std::map<TimerType, ITimerHandler*> timerTypeHandlers;

  public:
    TimerDistributor();
    virtual ~TimerDistributor();

    void registerTimerHandler(cMessage* timer, ITimerHandler* handler);
    void registerTimerHandler(TimerType type, ITimerHandler* handler);

    void deregisterTimerHandler(cMessage* timer, ITimerHandler* handler);
    void deregisterTimerHandler(TimerType type, ITimerHandler* handler);

    void distributeTimer(cMessage* timer);
    void distributeStartTimer(cMessage* timer);
  
};

}

#endif 