#ifndef _CRITICAL_PARAMETERREADER_H
#define _CRITICAL_PARAMETERREADER_H

#include "critical/parameters/CriticalProtocolParameters.h"
#include <omnetpp.h>

using namespace omnetpp;

namespace critical {

class ParameterReader {
  private:
    cModule* protocol = nullptr;

  public:
    CriticalProtocolParameters readParams(cModule* protocol);

  private:
    cPar& par(const char* name){ return protocol->par(name); };


    void validateParams(const CriticalProtocolParameters& params);

    RoutingProtocol getRoutingProtocol();
    BudgetAllocator getAllocater();
    LsAlgorithm getLsAlgorithm();
    LsUpdateStrategy getLsUpdateStrategy();
    ProbingVariant getProbingVariant();
    ProbingQueueHeuristic getProbingQueueHeuristic();

};


}



#endif 