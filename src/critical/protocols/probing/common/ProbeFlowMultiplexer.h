#ifndef _CRITICAL_PROBEFLOWMULTIPLEXER_H
#define _CRITICAL_PROBEFLOWMULTIPLEXER_H

#include "critical/common/handler/multiplex/FlowMultiplexer.h"
#include "critical/protocols/probing/common/Helpers.h"

namespace critical {

namespace probing {

class ProbeFlowMultiplexer: public FlowMultiplexer {
  public:
    ProbeFlowMultiplexer(MessageHandlerBase* parent, std::initializer_list<PacketType> types)
    : FlowMultiplexer(parent, types) {};
    virtual ~ProbeFlowMultiplexer() {};

  protected:
    virtual FlowId extractFlow(const inet::Packet* const rawPacket) override {
      return extractFlowFromProbingPacket(rawPacket);
    };
};

}

}

#endif 