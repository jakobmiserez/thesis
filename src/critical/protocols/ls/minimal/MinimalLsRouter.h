#ifndef _CRITICAL_BASICLSROUTER_H
#define _CRITICAL_BASICLSROUTER_H

#include "critical/common/routing/RouterBase.h"
#include "critical/protocols/ls/lsa/LsaDatabase.h"
#include "critical/protocols/ls/topology/NetworkTopology.h"
#include "critical/protocols/ls/neighbor/NeighborTable.h"
#include "critical/protocols/ls/packets/PacketCreator.h"

namespace critical {

namespace ls {

/**
 * @brief A minimal Link-State routing protocol
 * 
 */
class MinimalLsRouter: public RouterBase, public LsaListener {
  protected:
    RouterId routerId;
    NeighborTable neighborTable;
    LsaDatabase lsas;
    NetworkTopology topology;
    PacketCreator packetCreator;

  private:
    bool updatesAutomatically;

  public:
    MinimalLsRouter(CriticalProtocol* protocol);
    virtual ~MinimalLsRouter();

    NeighborTable& getNeighborTable() { return neighborTable; };
    const NeighborTable& getNeighborTable() const { return neighborTable; };
    const RouterId& getRouterId() const { return routerId; };
    LsaDatabase& getLSAs() { return lsas; };
    PacketCreator& getPacketCreator() { return packetCreator; };
    NetworkTopology& getTopology() { return topology; };

    void setUpdatesAutomatically(bool updatesAutomatically) {
      this->updatesAutomatically = updatesAutomatically;
    };

    virtual void start(double delay) override;

    virtual void rebuild();

    virtual void handleLinkFailure(int interfaceId) override;

    virtual void onLsaAdded(const Lsa& lsa) override;
  
    virtual void onLsaUpdate(const Lsa& lsa, const LsaConnectivityChanges& connectivity) override;

    virtual void handleLinkFailure(const RouterId& at, const std::set<int> removedLinks);

  protected:
    virtual TopLevelMessageHandler* createMessageHandler() override;

  private:
    void rebuildRoutingTable();

};

}

}


#endif 