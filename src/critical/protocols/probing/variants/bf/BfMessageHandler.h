#ifndef _CRITICAL_BFMESSAGEHANDLER_H
#define _CRITICAL_BFMESSAGEHANDLER_H

#include "BfMultiplexer.h"
#include "critical/protocols/ls/minimal/MinimalLsMessageHandler.h"
#include "critical/protocols/probing/packets/ProbingPackets_m.h"
#include "critical/protocols/probing/common/FreeHandler.h"
#include "critical/protocols/probing/common/FreeFailureHandler.h"

namespace critical {

namespace probing {

class BfMessageHandler: public ls::MinimalLsMessageHandler {
  private:
    // Multiplexer for flow probe and prune, which share the same state
    BfMultiplexer multiplexer;
    // Flow free handler
    FreeHandler freeHandler;
    // Flow free failure handler;
    FreeFailureHandler freeFailureHandler;

  public: 
    BfMessageHandler(CriticalProtocol* protocol) 
    : ls::MinimalLsMessageHandler(protocol), 
      multiplexer(this), 
      freeHandler(this),
      freeFailureHandler(this) {};
    virtual ~BfMessageHandler() {};

    virtual uint64_t estimateMemoryFootprint() const override {
      return multiplexer.estimateMemoryFootprint();
    };

};

}

}


#endif 