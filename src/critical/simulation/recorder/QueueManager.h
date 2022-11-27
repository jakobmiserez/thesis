#ifndef _CRITICAL_QUEUEMANAGER_H
#define _CRITICAL_QUEUEMANAGER_H

#include "QueueRecorder.h"
#include <omnetpp.h>

using namespace omnetpp;

#include <vector>
#include <map>
#include <string>
#include <fstream>

namespace critical {

class QueueManager: public cISimulationLifecycleListener {
  private:
    std::string fname;
    std::ofstream out;

    static QueueManager* instance;

  public:
    QueueManager() {};
    virtual ~QueueManager() {};

    void init();

    virtual void lifecycleEvent(SimulationLifecycleEventType eventType, cObject *details) override;

    void recordConsumption(simtime_t t, QueueRecorderData* data);

    virtual void listenerRemoved() override {
      delete this;
    };

    static QueueManager* getInstance() {
      if (instance == nullptr) {
        instance = new QueueManager();
        instance->init();
      }
      return instance;
    };

  private:
    std::string getOutputFileName();

};

  
} // namespace critical



#endif 