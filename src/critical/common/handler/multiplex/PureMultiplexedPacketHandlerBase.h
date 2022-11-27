#ifndef _CRITICAL_MULTIPLEXEDPACKETHANDLERBASE_H
#define _CRITICAL_MULTIPLEXEDPACKETHANDLERBASE_H

#include "PureMultiplexedPacketHandler.h"
#include "critical/common/handler/base/PacketHandlerBase.h"

namespace critical {

template <class T, class R>
class PureMultiplexedPacketPacketHandlerBase: 
  public virtual PacketHandlerBase<T, R>,
  public PureMultiplexedPacketHandler {

  public:
    PureMultiplexedPacketHandlerBase(MessageHandlerBase* parent, PacketType type) 
    : PacketHandlerBase<T, R>(parent, type) {};

    virtual ~PureMultiplexedPacketHandlerBase() {};
};


}

#endif 