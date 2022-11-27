#ifndef _CRITICAL_PREDICTABLE_QUEUE_H
#define _CRITICAL_PREDICTABLE_QUEUE_H

#include "critical/queueing/dnc/curves/AffineArrivalCurve.h"
#include "critical/queueing/dnc/curves/RateLatencyServiceCurve.h"

#include <stdint.h>
#include <omnetpp.h>

using namespace omnetpp;

namespace critical {

class PredictableQueue {
  private:
    int index;
    uint64_t delayBudget;
    double delayBudgetInSeconds;

    // Buffer size in bits
    uint64_t bufferSizeBudget;
    AffineArrivalCurve arrival;
    RateLatencyServiceCurve service;

  public:
    PredictableQueue(int index, uint64_t delayBudget, uint64_t bufferSizeBudget = 0);
    ~PredictableQueue();

    int getIndex() const { return index; };

    /**
     * @brief Returns the delay budget in microseconds. This should NEVER be used 
     * in combination with the horizontal deviation. 
     * 
     * @return uint64_t 
     */
    uint64_t getDelayBudget() const { return delayBudget; };

    /**
     * @brief Returns the delay budget of this queue in seconds
     * 
     * @return double 
     */
    double getDelayBudgetInSeconds() const { return delayBudgetInSeconds; }

    void setBufferSizeBudget(uint64_t bufferSizeBudget) {
      this->bufferSizeBudget = bufferSizeBudget;
    };

    uint64_t getBufferSizeBudget() const { return bufferSizeBudget; };

    const AffineArrivalCurve& getArrivalCurve() const { return arrival; };
    void setArrivalCurve(const AffineArrivalCurve& arrival) { this->arrival = arrival; };

    const RateLatencyServiceCurve& getServiceCurve() const { return service; };
    void setServiceCurve(const RateLatencyServiceCurve& service) { this->service = service; };

    /**
     * @brief Get the upper bound on the queueing delay of a packet in this queue in seconds.
     * This corresponds to the horizontal deviation between the service curve and the 
     * arrival curve of this queue.
     */
    double getQueueingDelayBound() const;

    /**
     * @brief Get the upper bound on the buffer size requirements of this queue in bits. 
     * This corresponds to the vertical deviation between the service curve and the arrival 
     * curve of this queue.
     */
    double getBufferSizeBound() const;

    /**
     * @brief Checks if the given flow is allowed to be added to this queue.
     * @param flow The traffic flow modeled as an affine arrival curve
     */
    bool canAllocateFlow(const AffineArrivalCurve& flow) const;

    /**
     * @brief Adds the given flow to this queue. This performs no checks.
     * @param flow The traffic flow modeled as an affine arrival curve
     * @return The modified arrival curve for the next hop
     */
    AffineArrivalCurve allocateFlow(const AffineArrivalCurve& flow);

    /**
     * @brief Frees the given flow in this queue. 
     * 
     * @param flow The traffic flow modeled as an affine arrival curve
     */
    void freeFlow(const AffineArrivalCurve& flow);

    /**
     * @brief Computes the updated flow parameters if this flow would be embedded in this 
     * queue.
     * 
     * @param flow  The traffic flow modeled as an affine arrival curve
     * @return AffineArrivalCurve 
     */
    AffineArrivalCurve updatedFlowParams(const AffineArrivalCurve& flow) const;

    /**
     * @brief Checks if the constraints of this queue are violated or not
     * 
     * @return true 
     * @return false 
     */
    bool check() const;


};

}

#endif