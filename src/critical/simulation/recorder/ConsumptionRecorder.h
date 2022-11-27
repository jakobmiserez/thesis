#ifndef _CRITICAL_CONSUMPTIONRECORDER_H
#define _CRITICAL_CONSUMPTIONRECORDER_H

#include <omnetpp.h>

using namespace omnetpp;

namespace critical {

class ConsumptionRecorderData: public cObject {
  private:
    cModule* source;
    int interfaceId;
    double addedConsumption;
    double maxConsumption;

  public:
    ConsumptionRecorderData() {};
    ConsumptionRecorderData(
      cModule* source, 
      int interfaceId, 
      double addedConsumption, 
      double maxConsumption
    )
    : source(source), interfaceId(interfaceId), 
      addedConsumption(addedConsumption),
      maxConsumption(maxConsumption) {};

    cModule* getSource() { return source; };
    double getAddedConsumption() { return addedConsumption; };
    int getInterfaceId() { return interfaceId; };
    double getMaxConsumption() { return maxConsumption; };
};

class ConsumptionRecorder: public cResultRecorder {

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