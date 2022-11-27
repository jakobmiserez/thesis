#ifndef _CRITICAL_QUEUERECORDER_H
#define _CRITICAL_QUEUERECORDER_H

#include <omnetpp.h>

using namespace omnetpp;

namespace critical {

class QueueRecorderData: public cObject {
  private:
    cModule* source;
    int interfaceId;
    int queue;
    double horizontalDeviation;
    double maxHorizontalDeviation;
    double verticalDeviation;
    double maxVerticalDeviation;

  public:
    QueueRecorderData(){};
    QueueRecorderData(
      cModule* source,
      int interfaceId,
      int queue,
      double horizontalDeviation,
      double maxHorizontalDeviation,
      double verticalDeviation,
      double maxVerticalDeviation
    )
    : source(source), interfaceId(interfaceId), 
      queue(queue), horizontalDeviation(horizontalDeviation),
      maxHorizontalDeviation(maxHorizontalDeviation),
      verticalDeviation(verticalDeviation),
      maxVerticalDeviation(maxVerticalDeviation) {};

    cModule* getSource() { return source; };
    int getInterfaceId() { return interfaceId; };
    int getQueue() { return queue; }
    double getHorizontalDeviation() { return horizontalDeviation; };
    double getMaxHorizontalDeviation() { return maxHorizontalDeviation; };
    double getVerticalDeviation() { return verticalDeviation; };
    double getMaxVerticalDeviation() { return maxVerticalDeviation; }
};

class QueueRecorder: public cResultRecorder {

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