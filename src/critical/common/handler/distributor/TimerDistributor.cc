#include "TimerDistributor.h"

namespace critical {

TimerDistributor::TimerDistributor() {

}

TimerDistributor::~TimerDistributor() {

}

void TimerDistributor::registerTimerHandler(cMessage* timer, ITimerHandler* handler) {
  auto it = timerHandlers.find(timer);
  if (it != timerHandlers.end()) {
    throw "Cannot register a handler for the same timer twice";
  }
  timerHandlers[timer] = handler;
}

void TimerDistributor::registerTimerHandler(TimerType type, ITimerHandler* handler) {
  auto it = timerTypeHandlers.find(type);
  if (it != timerTypeHandlers.end()) {
    throw "Cannot register a handler for the same timer type twice";
  }
  timerTypeHandlers[type] = handler;
}
    
void TimerDistributor::deregisterTimerHandler(cMessage* timer, ITimerHandler* handler) {
  auto it = timerHandlers.find(timer);
  if (it != timerHandlers.end() && it->second == handler) {
    timerHandlers.erase(timer);
  }
}

void TimerDistributor::deregisterTimerHandler(TimerType type, ITimerHandler* handler) {
  auto it = timerTypeHandlers.find(type);
  if (it != timerTypeHandlers.end() && it->second == handler) {
    timerTypeHandlers.erase(type);
  }
}

void TimerDistributor::distributeTimer(cMessage* timer) {
  auto it = timerHandlers.find(timer);
  if (it != timerHandlers.end()) {
    it->second->handleTimer(timer);
  }
  else {
    TimerType type = timer->getKind();
    auto itt = timerTypeHandlers.find(type);
    if (itt != timerTypeHandlers.end()) {
      itt->second->handleTimer(timer);
    }
    else {
      EV_WARN << "No handler found for timer " << timer << "\n";
    }
  }
}

void TimerDistributor::distributeStartTimer(cMessage* timer) {
  for (auto it = timerHandlers.begin(); it != timerHandlers.end(); ++it) {
    it->second->handleStartTimer(timer);
  }
}

}