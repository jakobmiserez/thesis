#ifndef _CRITICAL_SIMPLEPREDICTABLEPORT_H
#define _CRITICAL_SIMPLEPREDICTABLEPORT_H

#include "PredictableQueue.h"
#include "critical/common/packet/CriticalPacketBase_m.h"
#include "critical/flows/Flow.h"
#include "critical/queueing/dnc/budget/IBudgetAllocator.h"
#include "critical/common/util/Parameterizable.h"

#include <vector>
#include <functional>
#include <omnetpp.h>

using namespace omnetpp;

namespace critical {

class CriticalProtocol;
struct ProtocolParams;

class SimplePredictablePort: public Parameterizable {
  protected:
    // link delay in microseconds 
    uint64_t linkDelay = 0; 
    // link rate in bps
    double linkRate = 0;

    std::vector<PredictableQueue> queues;
    int id;
    size_t numQueues;

  public:
    SimplePredictablePort(int id, size_t numQueues, CriticalProtocol* protocol);
    virtual ~SimplePredictablePort();

    int getId() const { return id; };
    size_t getNumQueues() const { return queues.size(); };
    const std::vector<PredictableQueue>& getQueues() const { return queues; };
    double getLinkRate() const { return linkRate; };

    /**
     * @brief Returns the link delay in microseconds
     * 
     * @return uint64_t 
     */
    uint64_t getLinkDelay() const { return linkDelay; };
    
    void setLinkDelay(uint64_t linkDelay) { this->linkDelay = linkDelay; };
    void setLinkDelayFromSeconds(double seconds);

    uint64_t getTotalDelay(int queue) const { return queues[queue].getDelayBudget() + linkDelay; };

    QueueInfo getQueueState(int queue) const;

    /**
     * @brief Initializes the queues with a link rate and a queueing delay budget.
     * 
     * @param linkRate The rate of the output link
     */
    virtual void initialize(double linkRate);

    /**
     * @brief Overrides the queues curves. The budget is kept
     * 
     * @param newQueues 
     */
    void override(std::vector<QueueInfo> newQueues);

    /**
     * @brief Checks if the given flow can be added to the given queue. This method checks not only 
     * if the flow can be added to the given queue, but also checks if adding the flow to that queue 
     * does not violate the constraints of the lower priority queues.
     * 
     * @param queue The index of the queue to add the flow to
     * @param flow The flow modeled as an affine arrival curve
     */
    bool canAllocateFlow(int queue, const FlowParameters& params, int* failedQueue = nullptr) const;

    /**
     * @brief Checks if the given flow can be embedded in any of the queues of this 
     * port.
     * 
     * @param params 
     * @param delay 
     */
    bool canAllocateFlow(const FlowParameters& params, uint64_t delay) const;

    /**
     * @brief Adds the given flow to the given queue. No checks are performed. Note that this also 
     * modifies the lower priority queues.
     * 
     * @param queue 
     * @param flow 
     * @return The modified flow parameters for the next hop
     */
    virtual FlowParameters allocateFlow(int queue, const FlowParameters& params);

    /**
     * @brief Gets the updated flow parameters if the flow would we embedded in this queue.
     * 
     * @param queue 
     * @param params 
     * @return FlowParameters 
     */
    FlowParameters updatedFlowParams(int queue, const FlowParameters& params) const;

    /**
     * @brief Frees the given flow in the given queue. Note that this also modifies the lower 
     * priority queues.
     * 
     * @param queue
     * @param flow 
     */
    virtual void freeFlow(int queue, const FlowParameters& flow);

    std::vector<QueueInfo> getQueueStates();

    bool check() const;

    void printQueueStates() const;

    private:
      void updateLowerQueues(int queue);
};

}


#endif