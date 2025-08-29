#ifndef _CRITICAL_FLOWRESPONSERECORDER_H
#define _CRITICAL_FLOWRESPONSERECORDER_H

#include "critical/simulation/recorder/FlowRecorderData.h"

#include <omnetpp.h>
#include <fstream>
#include <critical/flows/map/linear/LinearFlowMap.h>

using namespace omnetpp;

namespace critical {


class ProbeReservationManager: public cISimulationLifecycleListener {
  private:
    static ProbeReservationManager* instance;
    struct Data {
        uint32_t currentReservations;
        uint32_t maxReservations;
    };

  public:
    ProbeReservationManager() {};
    virtual ~ProbeReservationManager() {};

    void init();

    virtual void lifecycleEvent(SimulationLifecycleEventType eventType, cObject *details) override;

    void recordProbeReservation(const ProbeReservationData& data);

    virtual void listenerRemoved() override {
      delete this;
    };

    static ProbeReservationManager* getInstance() {
      if (instance == nullptr) {
        instance = new ProbeReservationManager();
        instance->init();
      }
      return instance;
    };

  private:
    std::string getOutputFileName();
    std::ofstream out;
    LinearFlowMap<Data> map;

};

class ProbeReservationRecorder: public cResultRecorder {

  protected:
    virtual void finish(cResultFilter *prev) override {};

    virtual void receiveSignal(cResultFilter *prev, simtime_t_cref t, bool b, cObject *details) override {};
    virtual void receiveSignal(cResultFilter *prev, simtime_t_cref t, long l, cObject *details) override {};
    virtual void receiveSignal(cResultFilter *prev, simtime_t_cref t, unsigned long l, cObject *details) override {};
    virtual void receiveSignal(cResultFilter *prev, simtime_t_cref t, double d, cObject *details) override {};
    virtual void receiveSignal(cResultFilter *prev, simtime_t_cref t, const SimTime& v, cObject *details) override {};
    virtual void receiveSignal(cResultFilter *prev, simtime_t_cref t, const char *s, cObject *details) override {};
    virtual void receiveSignal(cResultFilter *prev, simtime_t_cref t, cObject *obj, cObject *details) override;
};

}


#endif 