#ifndef _CRITICAL_LSROUTER_H
#define _CRITICAL_LSROUTER_H

#include "critical/protocols/ls/minimal/MinimalLsRouter.h"
#include "critical/protocols/ls/neighbor/NeighborTable.h"
#include "critical/protocols/ls/util/LsDefs.h"
#include "critical/protocols/ls/lsa/LsaDatabase.h"
#include "critical/protocols/ls/lsa/QosLsaDatabase.h"
#include "critical/protocols/ls/packets/PacketCreator.h"
#include "critical/protocols/ls/topology/NetworkTopology.h"
#include "critical/protocols/ls/topology/QueueLevelTopology.h"
#include "critical/protocols/ls/topology/accesscontrol/DisjointAccessControl.h"
#include "critical/protocols/ls/path/PathTable.h"

#include <omnetpp.h>

using namespace omnetpp;

namespace critical {

namespace ls {

class LsRouter: public MinimalLsRouter, public IConsumptionListener {
  private:
    NetworkTopology topology;
    QosLsaDatabase qosLsas;
    QueueLevelTopology queueLevelTopology;

    PathTable primaryPathTable;
    PathTable secondaryPathTable;
    LinearFlowMap<int> tries;

  public:
    LsRouter(CriticalProtocol* protocol);
    virtual ~LsRouter();

    QosLsaDatabase& getQosLSAs() { return qosLsas; };
    const QueueLevelTopology& getQueueLevelTopology() { return queueLevelTopology; };
    PathTable& getPrimaryPathTable() { return primaryPathTable; };
    PathTable& getSecondaryPathTable() { return secondaryPathTable; };
    LinearFlowMap<int>& getTriesTable() { return tries; };

    virtual void start(double delay) override;

    virtual RouteResult startRouting(
      const inet::Ipv6Address& source, 
      const inet::Ipv6Address& dest, 
      uint32_t label, 
      uint64_t delay,
      uint64_t bandwidth,
      uint64_t burst
    ) override;

    virtual void startFreeing(
      const inet::Ipv6Address& source, 
      const inet::Ipv6Address& dest, 
      uint32_t label
    ) override;

    virtual void rebuild() override;

    /**
     * @brief Handle a significant consumption change at the given link. This will trigger the 
     * sending of QoS LSAs.
     * 
     * @param id The id of the link
     */
    virtual void onConsumptionChange(int id, bool significant, bool up) override;

    /**
     * @brief Handles link failures at the given router in the network. This will free resources 
     * that broken paths use and reroute flows if necessary.
     * 
     * @param at 
     * @param removedLinks 
     */
    virtual void handleLinkFailure(const RouterId& at, const std::set<int> removedLinks) override;

    /**
     * @brief Sends out QoS LSAs for the given output port
     * 
     * @param interfaceId 
     */
    void sendOutQosLsa(int interfaceId);  

  protected:
    virtual TopLevelMessageHandler* createMessageHandler() override;

  private:
    void rebuildQueueLevelTopology();

};

}

}

#endif 