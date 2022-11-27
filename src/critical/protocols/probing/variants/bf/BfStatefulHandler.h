#ifndef _CRITICAL_BFSTATEFULHANDLER_H
#define _CRITICAL_BFSTATEFULHANDLER_H

#include "critical/common/handler/stateful/StatefulMessageHandler.h"
#include "critical/protocols/probing/packets/ProbingPackets_m.h"
#include "BfStates.h"
#include "BfProbeHandler.h"
#include "BfPruneHandler.h"
#include "BfConfirmHandler.h"

namespace critical {

namespace probing {

class BfStatefulHandler: public StatefulMessageHandler<BfState> {
  private:
    BfProbeHandler probeHandler;
    BfPruneHandler pruneHandler;
    BfConfirmHandler confirmHandler;

  public:
    BfStatefulHandler(CriticalProtocol* protocol, FlowId flow) 
    : StatefulMessageHandler<BfState>(protocol, BfState(flow)),
      probeHandler(this),
      pruneHandler(this),
      confirmHandler(this) {};
      
    virtual ~BfStatefulHandler() {
      state.clearAndDeleteQueue();
    };

};

}

}


#endif 