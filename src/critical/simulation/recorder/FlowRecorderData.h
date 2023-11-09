#ifndef _CRITICAL_FLOWREQUIREMENTS_H
#define _CRITICAL_FLOWREQUIREMENTS_H

#include <omnetpp.h>
#include "critical/flows/Flow.h"

using namespace omnetpp;

namespace critical {

class FlowRequirements: public cObject {
  private:
    FlowParameters params;
    cModule* source;
    cModule* sink;

  public:
    FlowRequirements() {};
    FlowRequirements(FlowParameters params, cModule* source, cModule* sink)
    : params(params), source(source), sink(sink) {};

    const FlowParameters& getFlowParameters() { return params; }
    cModule* getSource() { return source; }
    cModule* getSink() { return sink; }
};

class FlowResponseData: public cObject {
  private:
    cModule* source;
    FlowId id;
    bool accepted;
  
  public:
    FlowResponseData() {};
    FlowResponseData(cModule* source, FlowId id, bool accepted): source(source), id(id), accepted(accepted) {};

    cModule* getSource() { return source; };
    FlowId getId() { return id; };
    bool isAccepted() { return accepted; };
};

class FlowRequestData: public cObject {
  private:
    cModule* source;
    FlowId id;
  
  public:
    FlowRequestData() {};
    FlowRequestData(cModule* source, FlowId id): source(source), id(id) {};

    cModule* getSource() { return source; };
    FlowId& getFlowId() { return id; };
};

class FlowRerouteData: public cObject {
  private:
    cModule* source;
    bool accepted;

  public:
    FlowRerouteData() {};
    FlowRerouteData(cModule* source, bool accepted): source(source), accepted(accepted) {};

    cModule* getSource() { return source; };
    bool isAccepted() { return accepted; };
};

class FlowSignalingData: public cObject {
  private:
    FlowId id;
  
  public:
    FlowSignalingData() {};
    FlowSignalingData(const FlowId& id): id(id) {};

    FlowId& getId() { return id; };
};

}

#endif 