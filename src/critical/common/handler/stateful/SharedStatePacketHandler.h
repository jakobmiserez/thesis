#ifndef _CRITICAL_SHAREDSTATEPACKETHANDLER_H
#define _CRITICAL_SHAREDSTATEPACKETHANDLER_H

#include "critical/common/handler/base/PacketHandlerBase.h"
#include "critical/common/handler/stateful/StatefulMessageHandler.h"

namespace critical {

template <class T, class S, class R>
class SharedStatePacketHandler : public PacketHandlerBase<T, R> {
  public:
    SharedStatePacketHandler(StatefulMessageHandler<S>* parent, PacketType type)
    : PacketHandlerBase<T, R>(parent, type) {};

    virtual ~SharedStatePacketHandler() {};

    S& getSharedState() {
      StatefulMessageHandler<S>* p = (StatefulMessageHandler<S>*)(this->pparent);
      return p->getSharedState();
    }
};

}


#endif 