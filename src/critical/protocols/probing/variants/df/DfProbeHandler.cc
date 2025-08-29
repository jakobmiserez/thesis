#include "DfProbeHandler.h"

#include <optional>
#include "critical/common/util/FuncList.h"
#include "critical/queueing/Link.h"
#include "critical/protocols/probing/packets/PacketCreator.h"

namespace critical {

namespace probing {

DfProbeHandler::DfProbeHandler(StatefulMessageHandler<DfState>* parent)
: SharedStatePacketHandler<FlowProbePacket, DfState, ProbingRouter>(parent, PROBE_PROBE) {

}

DfProbeHandler::~DfProbeHandler() {
  delete getSharedState().probe;
}

bool DfProbeHandler::handleMultiplexedPacket(const inet::Packet* rawPacket) {
  EV_INFO << "Handling flow probe packet\n";
  preprocessPacket(rawPacket);

  auto& state = getSharedState();

  EV_INFO << "(DF PROBE HANDLER) " << packetData.data->getFlow() << "\n";

  if (!isFirstPacket()) {
    EV_ERROR << "Detected routing loop\n";
    sendPacket(PacketCreator::createFlowPrunePacket(state.flow), packetData.sourceInterface);
    return false;
  }

  state.params = packetData.data->getParams();
  state.incomingInterface = packetData.sourceInterface;
  state.isFirstHop = packetData.sourceInterface == pparent->getProtocol()->getLo()->getInterfaceId();
  state.triedInterfaces.insert(packetData.sourceInterface);
  state.probe = packetData.data->dup();

  EV_INFO << "(DF PROBE HANDLER) " << state.flow << "\n";

  if (router->isDestinationRouterFor(state.flow.dest)) {
    return handleAtDestination();
  }

  return handleProbing();
}

bool DfProbeHandler::handleAtDestination() {
  EV_INFO << "(DF PROBE HANDLER) Handling probe at destination\n"; 
  auto& state = getSharedState();
  auto& ft = getFlowTable();

  if (!router->isLocalAddress(state.flow.dest)) {
    int id = router->getRouteFor(state.flow.dest)->interface;
    auto port = router->getPortById(id);

    auto links = port->getPossibleLinks(state.params, packetData.data->getStats().accumulatedDelay);
    if (links.size() == 0) {
      sendPacketBack(PacketCreator::createFlowPrunePacket(state.flow));
      return true;
    }

    auto link = links[0];
    link.allocate(state.params);

    // Edge case when dealing with link failure
    if (ft.contains(state.flow)) {
      auto [_, entry] = ft.deleteFlow(state.flow.src, state.flow.dest, state.flow.label);
      router->getOldFlows().insertFlow(state.flow, entry);
    }

    ft.embedFlow(
      state.flow,
      state.params,
      link.getInterfaceId(),
      state.flow.dest,
      state.incomingInterface,
      link.getQueue(),
      true,
      state.isFirstHop
    );
  }

  getProtocol()->onProbeReservation(state.flow, 1);
  getProtocol()->onPathSignaling(state.flow);

  sendPacketBack(PacketCreator::createFlowConfirmPacket(state.flow));
  return true;
}

bool DfProbeHandler::handleProbing() {
  EV_INFO << "(DF PROBE HANDLER) Trying to forward probe\n"; 
  auto& state = getSharedState();
  auto& data = packetData.data;

  auto res = router->getPortsFunc(state.triedInterfaces)
    .mapKeep<Route>([this, state, data](PredictablePort* port) {
      return router->getProbingRoute(port, state.flow.dest, state.params, data->getStats());
    })
    .filter([](const std::pair<PredictablePort*, Route>& pair) {
      return pair.second.isViable();
    })
    .findArgMin<double>([](const std::pair<PredictablePort*, Route>& pair) {
      return pair.second.cost;
    });


  if (!res.has_value()) {
    if (!state.isFirstHop) 
      sendPacket(PacketCreator::createFlowPrunePacket(state.flow), state.incomingInterface);
    else 
      getProtocol()->signalRoutingFailed(state.flow);
    return true;
  }

  auto& [port, route] = res.value();

  auto link = router->getAllocationStrategy().chooseQueue(port, packetData.data, route);
  auto newParams = link.allocate(state.params);
  getProtocol()->onProbeReservation(state.flow, 1);
  
  state.outgoingInterface = link.getInterfaceId();
  state.queue = link.getQueue();

  sendPacket(
    PacketCreator::createFlowProbePacket(state.probe, newParams, link.getDelay()),
    link.getInterfaceId()
  );
  
  return false;
}

}

}