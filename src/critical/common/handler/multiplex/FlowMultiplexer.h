#ifndef _CRITICAL_MULITPLEXEDPACKETHANDLER_H
#define _CRITICAL_MULITPLEXEDPACKETHANDLER_H

#include "critical/common/handler/base/MessageHandlerBase.h"
#include "critical/common/handler/singleplex/SingleplexPacketHandler.h"
#include "critical/flows/map/IFlowMap.h"

namespace critical {

class FlowMultiplexer: public SingleplexPacketHandler {
  private:
    IFlowMap<IPacketHandler*>* handlers;
    std::set<IPacketHandler*> createdHandlers;
    std::initializer_list<PacketType> types;
  protected:
    MessageHandlerBase* parent;

  public:
    FlowMultiplexer(MessageHandlerBase* parent, std::initializer_list<PacketType> types);
    virtual ~FlowMultiplexer(); 

    virtual void handlePacket(const inet::Packet* const rawPacket) override;

  protected:
    void removeFlow(FlowId flow);
    virtual FlowId extractFlow(const inet::Packet* const rawPacket) = 0;
    virtual IPacketHandler* createNewHandler(FlowId flow) = 0;


};

}


#endif 