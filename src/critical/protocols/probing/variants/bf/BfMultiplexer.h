#ifndef _CRITICAL_BFMULTIPLEXER_H
#define _CRITICAL_BFMULTIPLEXER_H

#include "critical/protocols/probing/common/ProbeFlowMultiplexer.h"
#include "critical/protocols/probing/packets/ProbingPackets_m.h"
#include "BfStatefulHandler.h"

namespace critical {

namespace probing {

class BfMultiplexer: public ProbeFlowMultiplexer {
  public:
    BfMultiplexer(MessageHandlerBase* parent)
    : ProbeFlowMultiplexer(parent, {
        PROBE_PROBE, 
        PROBE_PRUNE, 
        PROBE_CONFIRM
      }) {};
    virtual ~BfMultiplexer() {};

    virtual IPacketHandler* createNewHandler(FlowId flow) override {
      return new BfStatefulHandler(parent->getProtocol(), flow);
    };
};

}

}


#endif 