#include "PacketCreator.h"

namespace critical {

namespace probing {

inet::Packet* PacketCreator::createInitialFlowProbePacket(
  inet::Ipv6Address source,
  inet::Ipv6Address destination,
  uint32_t label,
  uint64_t burst,
  uint64_t bandwidth,
  uint64_t delay,
  uint32_t totalHopEstimate
) {
  FlowId flow(source, destination, label);
  FlowParameters params(delay, bandwidth, burst);
  FlowProbeStats stats;
  stats.accumulatedDelay = 0;
  stats.hops = 0;
  stats.totalHopEstimate = totalHopEstimate;

  return createFlowProbePacket(flow, params, stats);
}

inet::Packet* PacketCreator::createFlowProbePacket(
  const FlowId& flow,
  const FlowParameters& params,
  FlowProbeStats stats
) {
  auto packet = inet::makeShared<FlowProbePacket>();
  packet->setFlow(flow);
  packet->setParams(params);
  packet->setStats(stats);
  
  return wrap(packet, "PROBE");
}

inet::Packet* PacketCreator::createFlowProbePacket(
  const FlowProbePacket* previousProbe,
  const FlowParameters& newParams,
  uint64_t delayToAdd
) {
  FlowProbeStats stats = previousProbe->getStats();
  stats.accumulatedDelay += delayToAdd;
  stats.hops += 1;

  return createFlowProbePacket(previousProbe->getFlow(), newParams, stats);
}

inet::Packet* PacketCreator::createFlowPrunePacket(const FlowId& flow) {
  auto packet = inet::makeShared<FlowPrunePacket>();
  packet->setFlow(flow);
  return wrap(packet, "PRUNE");
}

inet::Packet* PacketCreator::createFlowFreePacket(const FlowId& flow) {
  inet::Ptr<FlowFreePacket> packet = inet::makeShared<FlowFreePacket>();
  packet->setFlow(flow);

  return wrap(packet, "FREE"); 
}

inet::Packet* PacketCreator::createFlowFreeFailurePacket(const FlowId& flow) {
  inet::Ptr<FlowFreeFailurePacket> packet = inet::makeShared<FlowFreeFailurePacket>();
  packet->setFlow(flow);

  return wrap(packet, "FREE-FAILURE");
}

inet::Packet* PacketCreator::createFlowConfirmPacket(const FlowId& flow) {
  inet::Ptr<FlowConfirmPacket> packet = inet::makeShared<FlowConfirmPacket>();
  packet->setFlow(flow);

  return wrap(packet, "CONFIRM");
}

}

}