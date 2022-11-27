#ifndef _CRITICAL_BASICMESSAGEHANDLER_H
#define _CRITICAL_BASICMESSAGEHANDLER_H

#include "critical/protocols/ls/handler/LsHelloHandler.h"
#include "critical/protocols/ls/handler/LsLsaHandler.h"

namespace critical {

namespace ls {

class MinimalLsMessageHandler: public TopLevelMessageHandler {
  protected:
    LsHelloHandler helloHandler;
    LsLsaHandler lsaHandler;

  public:
    MinimalLsMessageHandler(CriticalProtocol* protocol)
    : TopLevelMessageHandler(protocol),
      helloHandler(this),
      lsaHandler(this) {};
    virtual ~MinimalLsMessageHandler() {};

};

}

}


#endif 