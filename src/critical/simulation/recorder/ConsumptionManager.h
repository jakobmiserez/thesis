#ifndef _CRITICAL_CONSUMPTIONMANAGER_H
#define _CRITICAL_CONSUMPTIONMANAGER_H

#include <omnetpp.h>

using namespace omnetpp;

#include <vector>
#include <map>
#include <string>
#include <fstream>

namespace critical {

class ConsumptionManager: public cISimulationLifecycleListener {
  private:
    struct Data {
      std::string source;
      simtime_t time = -1;
      int interfaceId = -1;
      double consumption;
    };
    std::string fname;
    std::ofstream out;

    static ConsumptionManager* instance;

  public:
    ConsumptionManager() {};
    virtual ~ConsumptionManager() {};

    void init();

    virtual void lifecycleEvent(SimulationLifecycleEventType eventType, cObject *details) override;

    void recordConsumption(
      cModule* source, simtime_t t, int interfaceId, 
      double addedConsumption, double maxConsumption
    );

    virtual void listenerRemoved() override {
      delete this;
    };

    static ConsumptionManager* getInstance() {
      if (instance == nullptr) {
        instance = new ConsumptionManager();
        instance->init();
      }
      return instance;
    };

  private:
    std::string getOutputFileName();

};

  
} // namespace critical



#endif 