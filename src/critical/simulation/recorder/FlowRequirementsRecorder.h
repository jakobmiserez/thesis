#ifndef _CRITICAL_FLOWREQUIREMENTSRECORDER_H
#define _CRITICAL_FLOWREQUIREMENTSRECORDER_H

#include <omnetpp.h>
#include <vector>

#include "FlowRecorderData.h"

#include <fstream>

using namespace omnetpp;

namespace critical {

class FlowRequirementsRecorder: public cResultRecorder {
  public:
    FlowRequirementsRecorder() {};
    virtual ~FlowRequirementsRecorder() {};

  protected:
    virtual void finish(cResultFilter *prev) override;

    virtual void receiveSignal(cResultFilter *prev, simtime_t_cref t, bool b, cObject *details) override;
    virtual void receiveSignal(cResultFilter *prev, simtime_t_cref t, long l, cObject *details) override;
    virtual void receiveSignal(cResultFilter *prev, simtime_t_cref t, unsigned long l, cObject *details) override;
    virtual void receiveSignal(cResultFilter *prev, simtime_t_cref t, double d, cObject *details) override;
    virtual void receiveSignal(cResultFilter *prev, simtime_t_cref t, const SimTime& v, cObject *details) override;
    virtual void receiveSignal(cResultFilter *prev, simtime_t_cref t, const char *s, cObject *details) override;
    virtual void receiveSignal(cResultFilter *prev, simtime_t_cref t, cObject *obj, cObject *details) override;

  private:
    void init();

  private:
    bool isInit = false;
    std::ofstream out;
    std::string getOutputFileName();
};

}

#endif 