#ifndef _CRITICAL_DFBFMULTIPLEXER_H
#define _CRITICAL_DFBFMULTIPLEXER_H

#include "critical/protocols/probing/common/ProbeFlowMultiplexer.h"
#include "critical/protocols/probing/packets/ProbingPackets_m.h"
#include "critical/protocols/probing/variants/df/DfStatefulHandler.h"

namespace critical {

namespace probing {

class DfMultiplexer: public ProbeFlowMultiplexer {
  public:
    DfMultiplexer(MessageHandlerBase* parent)
    : ProbeFlowMultiplexer(parent, {
        PROBE_CONFIRM, 
        PROBE_PROBE, 
        PROBE_PRUNE
      }) {};
    virtual ~DfMultiplexer() {};

  protected:
    virtual IPacketHandler* createNewHandler(FlowId id) override {
      return new DfStatefulHandler(parent->getProtocol(), id);
    };
};

}
  
} // namespace critical




#endif 