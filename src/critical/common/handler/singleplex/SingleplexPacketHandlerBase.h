#ifndef _CRITICAL_SINGLEPLEXPACKETHANDLERBASE_H
#define _CRITICAL_SINGLEPLEXPACKETHANDLERBASE_H

#include "critical/common/handler/base/PacketHandlerBase.h"
#include "SingleplexPacketHandler.h"

namespace critical {

template <class T, class R>
class SingleplexPacketHandlerBase
: public PacketHandlerBase<T, R>,
  public SingleplexPacketHandler {

  public:
    SingleplexPacketHandlerBase(MessageHandlerBase* parent, PacketType type)
    : PacketHandlerBase<T, R>(parent, type) {}; 
    virtual ~SingleplexPacketHandlerBase() {};
};

}

#endif 