#ifndef _CRITICAL_FLOWRESPONSERECORDER_H
#define _CRITICAL_FLOWRESPONSERECORDER_H

#include <omnetpp.h>

using namespace omnetpp;

namespace critical {

class FlowResponseRecorder: public cResultRecorder {

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