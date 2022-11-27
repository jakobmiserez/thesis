#include "PacketCreator.h"

#include "critical/protocols/ls/packets/LsPackets_m.h"
#include "critical/protocols/ls/minimal/MinimalLsRouter.h"
#include "critical/common/util/FuncList.h"
#include "critical/protocols/ls/topology/QueueLevelTopologyLinkEncoding.h"

namespace critical {

namespace ls {

PacketCreator::PacketCreator(MinimalLsRouter* router): router(router), lsaSequenceNumber(0) {

}

PacketCreator::~PacketCreator() {

}

inet::Packet* PacketCreator::createHelloPacket() {
  inet::Ptr<LsHelloPacket> packet = inet::makeShared<LsHelloPacket>();
  packet->setRouterId(router->getRouterId());
  return wrap(packet, "hello");
}

inet::Packet* PacketCreator::createLsa() {
  inet::Ptr<LsaPacket> packet = inet::makeShared<LsaPacket>();
  const auto& table = router->getNeighborTable();

  packet->setSequenceNumber(getNextLsaSequenceNumber());
  packet->setRouterId(router->getRouterId());

  size_t fullyAdjacentCount = table.getFullyAdjacentCount();
  size_t networkCount = table.getNetworkCount();

  packet->setNetworkEntriesCount(networkCount);
  packet->setNeighborEntriesArraySize(fullyAdjacentCount);
  packet->setNetworkEntriesArraySize(networkCount);

  size_t i = 0, j = 0;
  for (const auto& [_, entry]: table) {
    const PredictablePort* port = router->getPortById(entry.interfaceId);
    if (entry.isFullyAdjacent()) {
      LinkStateNeighborEntry n;
      n.setNetwork(entry.network);
      n.setPrefixLength(entry.prefixLength);
      n.setNeighborId(entry.neighborId);
      n.setCost(1);
      n.setBw(port->getLinkRate());
      n.setDelay(port->getLinkDelay());
      n.setLinkId(port->getId());
      n.setNumQueues(port->getNumQueues());

      packet->setNeighborEntries(i++, n);
    }
    else if (!entry.isDown()) {
      LinkStateNetworkEntry n;
      n.setNetwork(entry.network);
      n.setPrefixLength(entry.prefixLength);
      n.setLinkId(port->getId());
      n.setNumQueues(port->getNumQueues());

      packet->setNetworkEntries(j++, n);
    }
  }

  // Set correct chunk length 
  inet::B base = packet->getChunkLength();
  inet::B arrays = inet::B(fullyAdjacentCount * 53) + inet::B(networkCount * 20);

  packet->setChunkLength(base + arrays);

  return wrap(packet, "lsa");
}

inet::Packet* PacketCreator::dupLsa(const LsaPacket* lsaPacket) {
  inet::Ptr<LsaPacket> packet = inet::makeShared<LsaPacket>();
  *packet = *lsaPacket;

  return wrap(packet, "lsa");
}

inet::Packet* PacketCreator::createQosLsa(int interfaceId) {
  inet::Ptr<QosLsaPacket> lsa = inet::makeShared<QosLsaPacket>();

  const PredictablePort* port = router->getPortById(interfaceId);
  lsa->setRouterId(router->getRouterId());
  lsa->setQueuesArraySize(port->getNumQueues());
  lsa->setSequenceNumber(getNextLsaQosSequenceNumber(interfaceId));
  lsa->setLinkId(port->getId());

  for (const auto& queue: port->getQueues()) {
    QueueInfo info;
    const AffineArrivalCurve& curve = queue.getArrivalCurve();
    info.burst = curve.getBurst();
    info.rate = curve.getRate();

    lsa->setQueues(queue.getIndex(), info);
  }

  lsa->setChunkLength(lsa->getChunkLength() + inet::B(16 * port->getNumQueues()));
  
  return wrap(lsa, "qos-lsa");
}

inet::Packet* PacketCreator::dupQosLsa(const QosLsaPacket* qosLsaPacket) {
  inet::Ptr<QosLsaPacket> lsa = inet::makeShared<QosLsaPacket>();
  *lsa = *qosLsaPacket;

  return wrap(lsa, "qos-lsa");
}

inet::Packet* PacketCreator::createEmbedPacket(const Flow& flow, const std::vector<const Topology::Link*>& path) {
  inet::Ptr<LsEmbedPacket> fe = inet::makeShared<LsEmbedPacket>();
  fe->setRouterId(router->getRouterId());
  fe->setFlow(flow);
  fe->setHop(0);
  fe->setPathArraySize(path.size());
  for (int i = 0; i < path.size(); i++) {
    fe->setPath(i, QueueLevelTopologyLinkEncoding::decodeLink(path[i]->getId()));
  }

  fe->setChunkLength(fe->getChunkLength() + inet::B(4 * path.size()));
  
  return wrap(fe, "Flow embed");
}

inet::Packet* PacketCreator::updateEmbedPacket(const LsEmbedPacket* flowEmbedPacket, const FlowParameters& updatedParams) {
  inet::Ptr<LsEmbedPacket> fe = inet::makeShared<LsEmbedPacket>();
  Flow flow(flowEmbedPacket->getFlow().id, updatedParams);
  fe->setRouterId(flowEmbedPacket->getRouterId());
  fe->setFlow(flow);
  fe->setHop(flowEmbedPacket->getHop() + 1);
  size_t entries = flowEmbedPacket->getPathArraySize();

  fe->setPathArraySize(entries);
  for (int i = 0; i < entries; i++) {
    fe->setPath(i, flowEmbedPacket->getPath(i));
  }
  fe->setChunkLength(fe->getChunkLength() + inet::B(entries * 4));
  return wrap(fe, "Flow embed");
}

inet::Packet* PacketCreator::createEmbedConfirmPacket(const FlowId& flow) {
  auto packet = inet::makeShared<LsEmbedConfirmPacket>();
  packet->setFlow(flow);
  return wrap(packet, "Flow embed confirm");
}

inet::Packet* PacketCreator::createEmbedFailPacket(const FlowId& flow) {
  auto packet = inet::makeShared<LsEmbedFailPacket>();
  packet->setRouterId(router->getRouterId());
  packet->setFlow(flow);
  return wrap(packet, "Flow embed fail");
}

uint32_t PacketCreator::getNextLsaSequenceNumber() {
  if (lsaSequenceNumber == 0xffffffff) {
    lsaSequenceNumber = 0;
  }
  return lsaSequenceNumber++;
}

uint32_t PacketCreator::getNextLsaQosSequenceNumber(int interfaceId) {
  auto it = nextQosSequenceNumbers.find(interfaceId);
  if (it == nextQosSequenceNumbers.end()) {
    nextQosSequenceNumbers[interfaceId] = 1;
  }

  uint32_t haha = nextQosSequenceNumbers[interfaceId];
  if (haha == 0xffffffff) {
    throw cRuntimeError("We made it here");
  }
  
  return nextQosSequenceNumbers[interfaceId]++;
}

}

}