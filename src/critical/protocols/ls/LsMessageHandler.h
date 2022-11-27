#ifndef _CRITICAL_LS_MESSAGEHANDLER_H
#define _CRITICAL_LS_MESSAGEHANDLER_H

#include "critical/protocols/ls/minimal/MinimalLsMessageHandler.h"
#include "critical/protocols/ls/handler/LsEmbedHandler.h"
#include "critical/protocols/ls/handler/LsQosLsaHandler.h"
#include "critical/protocols/ls/handler/LsEmbedConfirmHandler.h"
#include "critical/protocols/ls/handler/LsEmbedFailHandler.h"

namespace critical {

namespace ls {

class LsMessageHandler: public MinimalLsMessageHandler {
  private:
    LsEmbedHandler embedHandler;
    LsQosLsaHandler qosLsaHandler;
    LsEmbedConfirmHandler embedConfirmHandler;
    LsEmbedFailHandler embedFailHandler;

  public:
    LsMessageHandler(CriticalProtocol* protocol)
    : MinimalLsMessageHandler(protocol),
      embedHandler(this),
      qosLsaHandler(this),
      embedConfirmHandler(this),
      embedFailHandler(this) {};
    virtual ~LsMessageHandler() {};
  
};

}

}


#endif 