#include "FlowMultiplexer.h"

#include "critical/flows/map/linear/LinearFlowMap.h"

#include <omnetpp.h>

using namespace omnetpp;

namespace critical {

FlowMultiplexer::FlowMultiplexer(MessageHandlerBase* parent, std::initializer_list<PacketType> types) 
  : types(types), parent(parent) {

  for (PacketType type: types) {
    parent->registerPacketHandler(this, type);
  }
  handlers = new LinearFlowMap<IPacketHandler*>();
}

FlowMultiplexer::~FlowMultiplexer() {
  for (PacketType type: types) {
    parent->deregisterPacketHandler(this, type);
  }

  // Delete created handlers
  for (auto& elem: createdHandlers) {
    delete elem;
  }

  delete handlers;
}

void FlowMultiplexer::handlePacket(const inet::Packet* const rawPacket) {
  FlowId flow = extractFlow(rawPacket);
  auto entry = handlers->lookupFlow(flow);
  if (entry == nullptr) {
    IPacketHandler* handler = createNewHandler(flow);

    createdHandlers.insert(handler);
    entry = handlers->insertFlow(flow, handler);
  }

  if (entry->data->handleMultiplexedPacket(rawPacket)) {
    removeFlow(flow);
  }
}

void FlowMultiplexer::removeFlow(FlowId flow) {
  auto entry = handlers->deleteFlow(flow);
  createdHandlers.erase(entry.data);

  EV_INFO << "Deleting handler (removeFlow) " << entry.data << "\n";
  delete entry.data;
}



}