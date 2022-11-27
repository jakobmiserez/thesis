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
    bool accepted;
  
  public:
    FlowResponseData() {};
    FlowResponseData(cModule* source, bool accepted): source(source), accepted(accepted) {};

    cModule* getSource() { return source; };
    bool isAccepted() { return accepted; };
};

class FlowRequestData: public cObject {
  private:
    cModule* source;
  
  public:
    FlowRequestData() {};
    FlowRequestData(cModule* source): source(source) {};

    cModule* getSource() { return source; };
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

}

#endif 