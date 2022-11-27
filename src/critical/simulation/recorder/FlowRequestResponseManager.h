#ifndef _CRITICAL_FlowRequestResponseManager_H
#define _CRITICAL_FlowRequestResponseManager_H

#include <omnetpp.h>

using namespace omnetpp;

#include <vector>
#include <map>
#include <string>

namespace critical {

class FlowRequestResponseManager: public cISimulationLifecycleListener {
  private:
    struct Data {
      std::string source;
      simtime_t requestTime = -1;
      simtime_t responseTime = -1;
      bool accepted = false;
      simtime_t rerouteTime = -1;
      simtime_t rerouteAccepted = false;
    };
    std::string fname;
    std::map<int, int> map;
    std::vector<Data> list;

    static FlowRequestResponseManager
  * instance;

  public:
    FlowRequestResponseManager() {};
    virtual ~FlowRequestResponseManager() {};

    void init() {
      getEnvir()->addLifecycleListener(this);
      fname = getOutputFileName();
    };

    virtual void lifecycleEvent(SimulationLifecycleEventType eventType, cObject *details) override;

    void recordFlowRequest(cModule* source, simtime_t t);
    void recordFlowResponse(cModule* source, simtime_t t, bool accepted);
    void recordFlowReroute(cModule* source, simtime_t t, bool accepted);

    virtual void listenerRemoved() override {
      delete this;
    };

    static FlowRequestResponseManager* getInstance() {
      if (instance == nullptr) {
        instance = new FlowRequestResponseManager();
        instance->init();
      }
      return instance;
    };

  private:
    std::string getOutputFileName();

};

  
} // namespace critical



#endif 