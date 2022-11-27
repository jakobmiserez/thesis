#ifndef _CRITICAL_SINGLEPLEXPACKETHANDLER_H
#define _CRITICAL_SINGLEPLEXPACKETHANDLER_H

#include "critical/common/handler/IHandler.h"

namespace critical {

class SingleplexPacketHandler: public virtual IPacketHandler {
  public:
    virtual ~SingleplexPacketHandler() {};

    virtual bool handleMultiplexedPacket(const inet::Packet* const rawPacket) override {
      this->handlePacket(rawPacket);
      return false;
    };
};

}

#endif