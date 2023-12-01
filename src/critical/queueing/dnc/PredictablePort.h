#ifndef _CRITICAL_PREDICTABLE_PORT_H
#define _CRITICAL_PREDICTABLE_PORT_H

#include "PredictableQueue.h"
#include "SimplePredictablePort.h"

#include "critical/flows/Flow.h"
#include "critical/flows/FlowTable.h"
#include "critical/common/packet/CriticalPacketBase_m.h"
#include "critical/common/util/Observable.h"
#include "critical/queueing/dnc/consumption/ConsumptionChecker.h"
#include "critical/queueing/dnc/consumption/HybridConsumptionChecker.h"

#include <vector>
#include <functional>
#include <omnetpp.h>
#include <memory>

using namespace omnetpp;


namespace critical {

struct IConsumptionListener {
  virtual void onConsumptionChange(int id, bool significant, bool up) {};
};

class Link;

class PredictablePort
: public SimplePredictablePort, 
  public Observable<IConsumptionListener>,
  public IFlowTableListener {

  private: 
    HybridConsumptionChecker consumptionChecker;
    bool initializing = true;

    std::set<const FlowTableEntry*> registeredIncomingFlows;
    std::set<const FlowTableEntry*> registeredOutgoingFlows;

  public:
    PredictablePort(int id, int numQueues, CriticalProtocol* protocol);
    ~PredictablePort();

    const std::set<const FlowTableEntry*> getRegisteredIncomingFlows() const { return registeredIncomingFlows; };
    const std::set<const FlowTableEntry*> getRegisteredOutgoingFlows() const { return registeredOutgoingFlows; };
    const HybridConsumptionChecker& getConsumptionChecker() const { return consumptionChecker; };

    virtual void initialize(double linkRate) override;

    /**
     * @brief Get all possible queues that the given flow can be embedded in for this port.
     * 
     * @param flow 
     * @return std::vector<Link> 
     */
    std::vector<Link> getPossibleLinks(
      const FlowParameters& params, 
      uint64_t accumulatedDelay
    );


    virtual FlowParameters allocateFlow(int queue, const FlowParameters& params) override;

    virtual void freeFlow(int queue, const FlowParameters& flow) override;

    virtual void onFlowAccepted(const FlowTableEntry* entry) override;
    virtual void onFlowDelete(const FlowTableEntry* entry) override;

    // Make this class non-copyable
    PredictablePort(const PredictablePort&) = delete;
    PredictablePort& operator = (const PredictablePort&) = delete;
    PredictablePort(PredictablePort&&) = default;
    PredictablePort& operator=(PredictablePort&&) = default;

  private:
    void notifyConsumptionChange(bool significant, bool up);

};

}

#endif