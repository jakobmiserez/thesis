#ifndef _CRITICAL_FlowRequestResponseManager_H
#define _CRITICAL_FlowRequestResponseManager_H

#include <omnetpp.h>

using namespace omnetpp;

#include <vector>
#include <map>
#include <string>
#include <fstream>

#include "FlowRecorderData.h"

namespace critical {

class FlowRequestResponseManager: public cISimulationLifecycleListener {
  private:
    struct Data {
      std::string source;
      FlowId id;
      simtime_t requestTime = -1;
      simtime_t responseTime = -1;
      simtime_t signalingTime = -1;
      bool accepted = false;
    };
    std::ofstream out;
    std::ofstream outReroutes;
    std::map<FlowId, Data*> map;
    //std::vector<Data> list;

    static FlowRequestResponseManager* instance;

  public:
    FlowRequestResponseManager() {};
    virtual ~FlowRequestResponseManager() {};

    void init();

    virtual void lifecycleEvent(SimulationLifecycleEventType eventType, cObject *details) override;

    void recordFlowRequest(FlowRequestData* data, simtime_t t);
    void recordFlowResponse(FlowResponseData* data, simtime_t t);
    void recordFlowReroute(cModule* source, simtime_t t, bool accepted);
    void recordFlowSignaling(FlowSignalingData* data, simtime_t);

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
    std::string getReroutesOutputFileName();

};

  
} // namespace critical



#endif 