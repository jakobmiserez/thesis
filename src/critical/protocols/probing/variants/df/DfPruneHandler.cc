#include "DfPruneHandler.h"

#include "critical/protocols/probing/packets/PacketCreator.h"
#include "critical/queueing/Link.h"

#include <optional>

namespace critical {

namespace probing {

DfPruneHandler::DfPruneHandler(StatefulMessageHandler<DfState>* parent)
: SharedStatePacketHandler<FlowPrunePacket, DfState, ProbingRouter>(parent, PROBE_PRUNE) {

}

DfPruneHandler::~DfPruneHandler() {

}

bool DfPruneHandler::handleMultiplexedPacket(const inet::Packet* rawPacket) {
  EV_INFO << "Handling flow prune packet\n";
  preprocessPacket(rawPacket);

  EV_INFO << "(DF PRUNE HANDLER) " << getSharedState().flow << "\n";

  if (isFirstPacket()) {
    return true;
  }

  auto& state = getSharedState();

  // Deallocate the flow
  ASSERT(packetData.sourceInterface == state.outgoingInterface);
  router->getPortById(state.outgoingInterface)->freeFlow(state.queue, state.params);

  state.triedInterfaces.insert(state.outgoingInterface);

  auto res = router->getPortsFunc(state.triedInterfaces)
    .mapKeep<Route>([this, state](PredictablePort* port) {
      return router->getProbingRoute(port, state.flow.dest, state.params, state.probe->getStats());
    })
    .filter([](const std::pair<PredictablePort*, Route>& pair) {
      return pair.second.isViable();
    })
    .findArgMin<double>([](const std::pair<PredictablePort*, Route>& pair) {
      return pair.second.cost;
    });

  if (!res.has_value()) {
    getProtocol()->onProbeReservation(state.flow, -1);
    if (!state.isFirstHop) 
      sendPacket(PacketCreator::createFlowPrunePacket(state.flow), state.incomingInterface);
    else 
      getProtocol()->signalRoutingFailed(state.flow);
    return true;
  }

  auto& [port, route] = res.value();

  auto link = router->getAllocationStrategy().chooseQueue(port, state.probe, route);
  auto newParams = link.allocate(state.params);

  state.outgoingInterface = link.getInterfaceId();
  state.queue = link.getQueue();

  sendPacket(
    PacketCreator::createFlowProbePacket(state.probe, newParams, link.getDelay()),
    link.getInterfaceId()
  );

  // Don't report reservation, we still had one
  
  return false;
}

}

}