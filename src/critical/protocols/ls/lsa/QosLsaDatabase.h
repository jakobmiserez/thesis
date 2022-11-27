#ifndef _CRITICAL_QOSLSADATABASE_H
#define _CRITICAL_QOSLSADATABASE_H

#include "critical/protocols/ls/util/LsDefs.h"
#include "critical/protocols/ls/packets/LsPackets_m.h"
#include "critical/protocols/ls/lsa/LsaDatabase.h"
#include "critical/common/util/RoutingComponent.h"
#include "critical/queueing/dnc/SimplePredictablePort.h"

#include <omnetpp.h>
#include <map>

using namespace omnetpp;

namespace critical {

class CriticalProtocol;
class LsRouter;

namespace ls {

struct QosLsa {
  RouterId routerId = inet::Ipv6Address::UNSPECIFIED_ADDRESS;
  int linkId = 0;
  uint32_t sequenceNumber = 0;
  std::unique_ptr<SimplePredictablePort> port = nullptr;
};

class QosLsaDatabase: public LsaListener, public RoutingComponent<LsRouter> {
  private:
    std::map<RouterId, std::unordered_map<int, QosLsa>> database;
    LsaDatabase& lsas;

  public:
    QosLsaDatabase(LsaDatabase& lsas, CriticalProtocol* protocol);
    ~QosLsaDatabase();

    virtual void onLsaAdded(const Lsa& lsa) override;
    virtual void onLsaUpdate(const Lsa& lsa, const LsaConnectivityChanges& connectivityChanges) override;

    bool insertQosLsa(const QosLsaPacket* const qosLsaPacket);
    size_t size() const { return database.size(); };

    const SimplePredictablePort* getQueueStates(const RouterId& routerId, int linkId) const;

  private:
    QosLinkInfo toQosLsa(const QosLsaPacket* const qosLsaPacket);

    void adjustQueueStates(std::vector<QueueInfo>& queueStates, const std::vector<QueueInfo>& previousQueueStates);
};

}

}


#endif 