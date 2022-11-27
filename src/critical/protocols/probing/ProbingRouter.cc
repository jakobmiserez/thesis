#include "ProbingRouter.h"

#include "critical/CriticalProtocol.h"
#include "critical/protocols/probing/packets/ProbingPackets_m.h"
#include "critical/protocols/probing/packets/PacketCreator.h"
#include "critical/protocols/probing/variants/bf/BfMessageHandler.h"
#include "critical/protocols/probing/variants/df/DfMessageHandler.h"

#include <inet/linklayer/common/InterfaceTag_m.h>

namespace critical {

namespace probing {

ProbingRouter::ProbingRouter(CriticalProtocol* protocol)
: ls::MinimalLsRouter(protocol), 
  queueAllocationStrategy(getParams().probingQueueHeuristic) {

}

ProbingRouter::~ProbingRouter() {

}

RouterBase::RouteResult ProbingRouter::startRouting(
  const inet::Ipv6Address& source, 
  const inet::Ipv6Address& dest, 
  uint32_t label, 
  uint64_t delay,
  uint64_t bandwidth,
  uint64_t burst
) {
  EV_INFO << "Started probing protocol upon request\n";
  EV_INFO << "  - " << source << " -> " << dest << "\n";
  EV_INFO << "  - delay:     " << delay << "us\n";
  EV_INFO << "  - bandwidth: " << bandwidth << "bps\n";
  EV_INFO << "  - burst:     " << burst << "b\n";
  EV_INFO << "  - label:     " << label << "\n";

  uint32_t hops = (uint32_t)ipRoutingTable->findBestMatchingRoute(dest)->getMetric(); // (uint32_t)underlyingRoutingProtocol.getRoute(dest)->cost;
  EV_INFO << "Initial hop estimation: " << hops << "\n";

  // We will send a probing packet to the loopback interface.
  // This makes sure that the probing process happens transparently.    
  protocol->sendPacketLo(
    PacketCreator::createInitialFlowProbePacket(source, dest, label, burst, bandwidth, delay, hops)
  );

  // Indicate that the protocol starts asynchronously
  return ONGOING;
}

void ProbingRouter::startFreeing(
  const inet::Ipv6Address& source, 
  const inet::Ipv6Address& dest, 
  uint32_t label
) {
  EV_INFO << "Started freeing process\n";
  FlowId flow(source, dest, label);
  protocol->sendPacketLo(
    PacketCreator::createFlowFreePacket(flow)
  );
}

TopLevelMessageHandler* ProbingRouter::createMessageHandler() {
  switch (getParams().probingVariant) {
    case ProbingVariant::BREADTH_FIRST:
      return new BfMessageHandler(protocol);
    case ProbingVariant::DEPTH_FIRST:
    default:
      return new DfMessageHandler(protocol);
  }
}

Route ProbingRouter::getProbingRoute(
  PredictablePort* port, 
  const inet::Ipv6Address& dest,
  const FlowParameters& params, 
  FlowProbeStats stats
) {
  int id = port->getId();
  if (!neighborTable.getNeighbor(id).isFullyAdjacent()) 
    return Route(id, INF);
  if (!port->canAllocateFlow(params, stats.accumulatedDelay))
    return Route(id, INF);

  const inet::Ipv6Address& neighbor = neighborTable.getNeighbor(port->getId()).neighborId;
  double cost = topology.getAlternativeRouteCost(routerId, dest, neighbor);

  if (cost == INF) 
    return Route(id, INF);

  double costToGo = cost;
  double costDone = stats.hops;
  double estimatedCost = costToGo + costDone;
  double threshold = (double)stats.totalHopEstimate / 3.0 * 4.0 + 3;

  bool prune = estimatedCost > threshold; 
  if (prune) {
    EV_INFO << "Pruning!" << estimatedCost << " > " << threshold << " (" << stats.totalHopEstimate << ")\n";
    return Route(id, INF);
  }
  return Route(id, cost);
}

void ProbingRouter::handleLinkFailure(int interfaceId) {
  MinimalLsRouter::handleLinkFailure(interfaceId);
  auto& ft = protocol->getFlowTable();

  const PredictablePort* port = getPortById(interfaceId);
  const auto& incoming = port->getRegisteredIncomingFlows();
  const auto& outgoing = port->getRegisteredOutgoingFlows();
  std::set<const FlowTableEntry*> toDelete;

  for (const auto& entry: incoming) {
    toDelete.insert(entry);
    if (!entry->data.finalHop) {
      // Clear the upstream path
      messageHandler->sendPacket(
        PacketCreator::createFlowFreeFailurePacket(entry->flow), 
        inet::Ipv6Address::ALL_NODES_2,
        entry->data.nextInterface
      );
    }
  }

  for (const auto& entry: outgoing) {
    toDelete.insert(entry);

    if (!entry->data.firstHop) {
      // Clear the downstream path
      messageHandler->sendPacket(
        PacketCreator::createFlowFreeFailurePacket(entry->flow),
        inet::Ipv6Address::ALL_NODES_2,
        entry->data.prevInterface
      );
    }
    else {
      // We are the starting router, i.e. we should reroute this flow
      reroute(entry->flow, entry->data.params);
    }
  }

  for (const auto& entry: toDelete) {
    ft.deleteFlow(entry->flow.src, entry->flow.dest, entry->flow.label);
  }
}

}

}