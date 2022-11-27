#ifndef _CRITICAL_PUREMULTIPLEXEDPACKETHANDLER_H
#define _CRITICAL_PUREMULTIPLEXEDPACKETHANDLER_H

#include "critical/common/handler/IHandler.h"

namespace critical {

class PureMultiplexedPacketHandler: public virtual IPacketHandler {
  public:
    virtual ~PureMultiplexedPacketHandler() {};

    virtual void handlePacket(const inet::Packet* const rawPacket) override {
      throw cRuntimeError("A pure multiplexed packet handler cannot handle non-multiplexed packets");
    };
};

}

#endif 