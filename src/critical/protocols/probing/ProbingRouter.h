#ifndef _CRITICAL_PROBINGROUTER_H
#define _CRITICAL_PROBINGROUTER_H

#include "critical/queueing/dnc/PredictablePort.h"
#include "critical/protocols/probing/common/QueueAllocationStrategy.h"
#include "critical/protocols/probing/packets/ProbingPackets_m.h"
#include "critical/protocols/ls/minimal/MinimalLsRouter.h"
#include "critical/flows/map/linear/LinearFlowMap.h"

#include <omnetpp.h>

using namespace omnetpp;

namespace critical {

namespace probing {

class ProbingRouter : public ls::MinimalLsRouter {
  private:
    QueueAllocationStrategy queueAllocationStrategy;
    LinearFlowSet externalFlows;
    LinearFlowMap<FlowTableData> oldFlows;

  public:
    ProbingRouter(CriticalProtocol* protocol);
    virtual ~ProbingRouter();

    const QueueAllocationStrategy& getAllocationStrategy() { return queueAllocationStrategy; };

    LinearFlowSet& getExternalFlows() { return externalFlows; };
    LinearFlowMap<FlowTableData>& getOldFlows() { return oldFlows; }

    Route getProbingRoute(
      PredictablePort* port, 
      const inet::Ipv6Address& dest,
      const FlowParameters& params, 
      FlowProbeStats stats
    );

    //
    // Interface for protocol
    //

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

    virtual void handleLinkFailure(int interfaceId) override;

  protected:
    virtual TopLevelMessageHandler* createMessageHandler() override;

};

}

}

#endif