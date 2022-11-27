#include "QosLsaDatabase.h"

#include "critical/CriticalProtocol.h"
#include "critical/protocols/ls/LsRouter.h"

namespace critical {

namespace ls {

QosLsaDatabase::QosLsaDatabase(LsaDatabase& lsas, CriticalProtocol* protocol)
: RoutingComponent<LsRouter>(protocol),
  lsas(lsas) {
  lsas.addListener(this, ObservingPriority::HIGHEST);
}

QosLsaDatabase::~QosLsaDatabase() {
  lsas.removeListener(this);
}

void QosLsaDatabase::onLsaAdded(const Lsa& lsa) {
  if (lsa.id == router->getRouterId()) {
    return;
  }
  auto& entries = database[lsa.id];

  for (const auto& n: lsa.links) {
    QosLsa& qosLsa = entries[n.linkId];

    qosLsa.linkId = n.linkId;
    qosLsa.sequenceNumber = 0;
    qosLsa.routerId = lsa.id;

    qosLsa.port.reset(new SimplePredictablePort(n.linkId, n.numQueues, protocol));
    qosLsa.port->initialize((double)n.bw);
    qosLsa.port->setLinkDelay(n.delay);
  }
}

void QosLsaDatabase::onLsaUpdate(const Lsa& lsa, const LsaConnectivityChanges& connectivityChanges) {
  auto& entries = database[lsa.id];

  EV_INFO << "(QOS LSA DATABASE) Updated LSA from "<< inet::L3AddressResolver().findHostWithAddress(lsa.id)->getFullPath() << "\n";

  for (const auto& linkId: connectivityChanges.removedLinks) {
    EV_INFO << "(QOS LSA DATABASE) deleting link " << linkId << "\n";
    entries.erase(linkId);
  }

  for (const auto& link: lsa.links) {
    if (contains(connectivityChanges.addedLinks, link.linkId)) {
      QosLsa& qosLsa = entries[link.linkId];

      qosLsa.linkId = link.linkId;
      qosLsa.sequenceNumber = 0;
      qosLsa.routerId = lsa.id;

      qosLsa.port.reset(new SimplePredictablePort(link.linkId, link.numQueues, protocol));
      qosLsa.port->initialize(link.bw);
      qosLsa.port->setLinkDelay(link.delay);
    }
  }
}

bool QosLsaDatabase::insertQosLsa(const QosLsaPacket* const qosLsaPacket) {
  EV_INFO << "Inserting QoS lsa\n";
  const RouterId& routerId = qosLsaPacket->getRouterId();
  QosLinkInfo lsa = toQosLsa(qosLsaPacket);

  EV_INFO << "Link id: " << lsa.linkId << "\n";

  QosLsa& entry = database.at(routerId).at(lsa.linkId);

  EV_INFO << "here\n";

  if (lsa.sequenceNumber > entry.sequenceNumber) {
    protocol->qosOverrides++;
    entry.sequenceNumber = lsa.sequenceNumber;

    adjustQueueStates(lsa.queues, entry.port->getQueueStates());

    entry.port->override(lsa.queues);
    return true;
  }
  return false;
}

QosLinkInfo QosLsaDatabase::toQosLsa(const QosLsaPacket* const qosLsaPacket) {
  QosLinkInfo info;
  info.linkId = qosLsaPacket->getLinkId();
  info.sequenceNumber = qosLsaPacket->getSequenceNumber();

  for (int i = 0; i < qosLsaPacket->getQueuesArraySize(); i++) {
    const auto& queue = qosLsaPacket->getQueues(i);
    info.queues.push_back(queue);
  } 

  return info;
}

const SimplePredictablePort* QosLsaDatabase::getQueueStates(const RouterId& routerId, int linkId) const {
  if (routerId == router->getRouterId()) {
    return router->getPortById(linkId);
  }

  return database.at(routerId).at(linkId).port.get();
}


void QosLsaDatabase::adjustQueueStates(std::vector<QueueInfo>& queueStates, const std::vector<QueueInfo>& previousQueueStates) {
  for (int i = 0; i < queueStates.size(); i++) {
    QueueInfo& q1 = queueStates[i];
    const QueueInfo& q2 = previousQueueStates[i];

    double deltaBurst = q1.burst - q2.burst;
    double rateDelta = q1.rate - q2.rate;

    //q1.burst += 0.25 * deltaBurst;
    //q1.rate += 0.25 * rateDelta;
  }
}

}

}