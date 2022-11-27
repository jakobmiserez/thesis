#ifndef _CRITICAL_DFBFSTATEFULHANDLER_H
#define _CRITICAL_DFBFSTATEFULHANDLER_H

#include "critical/common/handler/stateful/StatefulMessageHandler.h"
#include "critical/protocols/probing/common/Helpers.h"
#include "DfStates.h"
#include "DfProbeHandler.h"
#include "DfConfirmHandler.h"
#include "DfPruneHandler.h"

namespace critical {

namespace probing {

class DfStatefulHandler: public StatefulMessageHandler<DfState> {
  private:
    DfProbeHandler probeHandler;
    DfPruneHandler pruneHandler;
    DfConfirmHandler confirmHandler;

  public:
    DfStatefulHandler(CriticalProtocol* protocol, FlowId flowId)
    : StatefulMessageHandler(protocol, DfState(flowId)),
      probeHandler(this),
      pruneHandler(this),
      confirmHandler(this) {};
    virtual ~DfStatefulHandler() {};
  
};

}

}


#endif 