#ifndef _CRITICAL_DFBFMESSAGEHANDLER_H
#define _CRITICAL_DFBFMESSAGEHANDLER_H

#include "critical/common/handler/top/TopLevelMessageHandler.h"
#include "critical/protocols/probing/common/FreeHandler.h"
#include "critical/protocols/probing/common/FreeFailureHandler.h"
#include "critical/protocols/probing/packets/ProbingPackets_m.h"
#include "critical/protocols/ls/minimal/MinimalLsMessageHandler.h"
#include "DfMultiplexer.h"

namespace critical {

namespace probing {

class DfMessageHandler: public ls::MinimalLsMessageHandler {
  private:
    DfMultiplexer multiplexer;
    FreeHandler freeHandler;
    FreeFailureHandler freeFailureHandler;

  public:
    DfMessageHandler(CriticalProtocol* protocol)
    : ls::MinimalLsMessageHandler(protocol),
      multiplexer(this),
      freeHandler(this),
      freeFailureHandler(this) {};
    ~DfMessageHandler() {};

};

}

}



#endif 