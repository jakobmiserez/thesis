#include "PredictableQueue.h"

#include <stddef.h>
#include "critical/queueing/dnc/curves/helpers.h"

namespace critical {

PredictableQueue::PredictableQueue(
  int index, 
  uint64_t delayBudget, 
  uint64_t bufferSizeBudget
): index(index), delayBudget(delayBudget), bufferSizeBudget(bufferSizeBudget),
   arrival(0, 0), service(0, 0) {
  delayBudgetInSeconds = (double)delayBudget / 1000000;
}

PredictableQueue::~PredictableQueue() {

}


bool PredictableQueue::canAllocateFlow(const AffineArrivalCurve& flow) const {
  const AffineArrivalCurve newArrival = arrival + flow;

  double hd = horizontalDeviation(newArrival, service);
  double vd = verticalDeviation(newArrival, service);

 return hd < (double)delayBudgetInSeconds && (bufferSizeBudget == 0 || vd < (double)bufferSizeBudget);
}

AffineArrivalCurve PredictableQueue::allocateFlow(const AffineArrivalCurve& flow) {
  arrival += flow;
  return updatedFlowParams(flow);
}

void PredictableQueue::freeFlow(const AffineArrivalCurve& flow) {
  arrival -= flow;
}

double PredictableQueue::getQueueingDelayBound() const {
  return horizontalDeviation(arrival, service);
}

double PredictableQueue::getBufferSizeBound() const {
  return verticalDeviation(arrival, service);
}

AffineArrivalCurve PredictableQueue::updatedFlowParams(const AffineArrivalCurve& flow) const {
  // According to my network calculus book, you should increase the burst with the 
  // vertical deviation between the service and the arrival curve. However, we cannot guarantee that the 
  // vertical deviation will not grow bigger once a flow is embedded.  
  //
  // Solution 1: use the port queue capacity (Silo)
  // Solution 2: use the horizontal deviation as upper bound (used here, as well as in Chameleon)
  // 
  // TODO: check this again (burst in bytes vs in bits????)
  double increase = flow.getRate() * delayBudgetInSeconds; 
  return AffineArrivalCurve(flow.getRate(), flow.getBurst() + increase);
}

bool PredictableQueue::check() const {
  double hd = getQueueingDelayBound();
  double vd = getBufferSizeBound();
  if (hd > getDelayBudgetInSeconds())
    return false;
  if (bufferSizeBudget > 0 && vd > (double)bufferSizeBudget)
    return false;
  return true;
}

}