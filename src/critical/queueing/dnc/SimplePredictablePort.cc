#include "SimplePredictablePort.h"

#include "critical/CriticalProtocol.h"
#include "critical/queueing/dnc/curves/helpers.h"
#include "critical/queueing/dnc/budget/BudgetAllocaterFactory.h"
#include "critical/queueing/dnc/curves/AffineArrivalCurve.h"
#include "critical/queueing/dnc/curves/RateLatencyServiceCurve.h"

namespace critical {

SimplePredictablePort::SimplePredictablePort(int id, size_t numQueues, CriticalProtocol* protocol)
: Parameterizable(protocol),
  id(id), numQueues(numQueues) {
  
}

SimplePredictablePort::~SimplePredictablePort() {

}

void SimplePredictablePort::setLinkDelayFromSeconds(double seconds) {
  uint64_t us = ceil(seconds * 1000000);
  linkDelay = us;
}

void SimplePredictablePort::initialize(double linkRate) {
  EV_INFO << "(PORT " << id << ") Initializing\n";
  EV_INFO << "Link rate is " << linkRate << "\n";
  ASSERT(linkRate > 0);
  const auto& protocolParams = getParams();

  IBudgetAllocator* allocator = BudgetAllocatorFactory::createNewAllocator(protocolParams.budgetAllocator);
  if (!allocator->check(numQueues)) {
    delete allocator;
    throw cRuntimeError("Unsupported number of queues: %i", numQueues);
  }
  this->linkRate = linkRate;

  RateLatencyServiceCurve defaultServiceCurve(linkRate);

  // Shift by the maximum packet size (in bits)
  defaultServiceCurve.shiftDown(24000);

  queues.clear();
  queues.reserve(numQueues);
  for (int i = 0; i < numQueues; i++) {
    auto& queue = queues.emplace_back(i, allocator->allocate(i, numQueues));
    queue.setServiceCurve(defaultServiceCurve);
    queue.setBufferSizeBudget(97000*8);

    /*
    
    // Get queue buffer size 
    char path[50];
    sprintf(path, ".ppp.queue.queue[%i]", i);
    auto& par = protocol->getInterfaceTable()->getInterfaceById(id)->getModuleByPath(path)->par("dataCapacity");
    if (par.intValue() > 0) {
      queue.setBufferSizeBudget(par.intValue());
    }
    */
  }
  delete allocator;

  // Allocate protocol resources
  uint64_t protocolLinkRate = ceil(linkRate * protocolParams.protocolBwUsage);
  FlowParameters params(0, protocolLinkRate, protocolParams.protocolBurstUsage);
  if (params.burst <= 0 || params.rate <= 0)
    return;

  int failedQueue = -1;
  if (!canAllocateFlow(protocolParams.protocolQueue, params, &failedQueue)) {
    std::string message = "Cannot allocate protocol resources without violating the queue budgets of queue ";
    message += std::to_string(failedQueue);
    throw cRuntimeError(message.c_str());
  }
  allocateFlow(protocolParams.protocolQueue, params);
}


void SimplePredictablePort::override(std::vector<QueueInfo> newQueues) {
  EV_INFO << "(SIMPLE PREDICTABLE PORT) Overriding queues\n";
  for (int i = 0; i < numQueues; i++) { 
    AffineArrivalCurve curve(newQueues[i].rate, newQueues[i].burst); 

    const auto& curve2 = queues[i].getArrivalCurve();
    EV_INFO << "Change "  << i << " : AffineArrivalCurve(" << 
      curve2.getBurst() << " -> " << curve.getBurst() << "," << 
      curve2.getRate() <<  " -> " << curve.getBurst() << ")\n";
    
    queues[i].setArrivalCurve(curve);
  }
  updateLowerQueues(0);
  ASSERT(check());
}

bool SimplePredictablePort::canAllocateFlow(int queue, const FlowParameters& params, int* failedQueue) const {
  auto flow = params.dncModel();

  // First check if the flow can be added to the desired queue
  if (!queues[queue].canAllocateFlow(flow)) {
    EV_INFO << "Single queue\n";
    if (failedQueue != nullptr)
      *failedQueue = queue;
    return false;
  }
  // Now, check if adding the queue would violate lower priority queues constraints

  bool allowed = true;

  // Keep track of the modified previous arrival and service curves
  AffineArrivalCurve prevArrival = queues[queue].getArrivalCurve() + flow;
  RateLatencyServiceCurve prevService = queues[queue].getServiceCurve();
  
  // Start at the next, lower priority queue
  int i = queue + 1;
  while (allowed && i < queues.size()) {
    // Fetch the current queue
    const PredictableQueue& lowerQueue = queues[i];

    // Fetch the new curves for this queue
    const RateLatencyServiceCurve newService = prevService - prevArrival;
    const AffineArrivalCurve& arrival = lowerQueue.getArrivalCurve();

    // Check if the curves violate the requirements 
    allowed = horizontalDeviation(arrival, newService) < lowerQueue.getDelayBudgetInSeconds();
    if (lowerQueue.getBufferSizeBudget() > 0) {
      allowed = allowed && verticalDeviation(arrival, newService) <= (double)lowerQueue.getBufferSizeBudget();
    }

    // Set the previous curves to the current curve for the next iteration
    prevArrival = arrival;
    prevService = newService;

    i++;
  }
  if (!allowed && failedQueue != nullptr)
    *failedQueue = queue - 1;

  return allowed;
}

bool SimplePredictablePort::canAllocateFlow(const FlowParameters& params, uint64_t delay) const {
  bool canAllocate = false;
  int i = 0;
  while (i < numQueues && !canAllocate) {
    const PredictableQueue& queue = queues[i];

    uint64_t d = delay + queue.getDelayBudget() + getLinkDelay();
    if (d > params.delay) {
      // lower queues will always violate this
      return false;
    }
    
    canAllocate = canAllocateFlow(i, params);
    i++;
  }
  return canAllocate;
}

FlowParameters SimplePredictablePort::allocateFlow(int queue, const FlowParameters& params) {
  const auto& res = queues[queue].allocateFlow(params.dncModel());
  updateLowerQueues(queue);

  return FlowParameters(params.delay, res.getRate(), res.getBurst());
}

FlowParameters SimplePredictablePort::updatedFlowParams(int queue, const FlowParameters& params) const {
  const auto res = queues[queue].updatedFlowParams(params.dncModel());
  return FlowParameters(params.delay, res.getRate(), res.getBurst());
}

void SimplePredictablePort::freeFlow(int queue, const FlowParameters& params) {
  queues[queue].freeFlow(params.dncModel());
  updateLowerQueues(queue);
}

void SimplePredictablePort::updateLowerQueues(int queue) {
  for (int i = queue + 1; i < queues.size(); i++) {
    const auto& previous = queues[i - 1];
    const auto& newService = previous.getServiceCurve() - previous.getArrivalCurve();

    queues[i].setServiceCurve(newService);
  }
  ASSERT(check());
}

QueueInfo SimplePredictablePort::getQueueState(int queue) const {
  const AffineArrivalCurve& arrival = getQueues()[queue].getArrivalCurve();

  QueueInfo q;
  q.burst = arrival.getBurst();
  q.rate = arrival.getRate();
  return q;
}

bool SimplePredictablePort::check() const {
  for (int i = 0; i < numQueues; i++) {
    if (!queues[i].check())
      return false;
  }
  if (queues[0].getServiceCurve().getRate() > (double)linkRate) {
    return false;
  }
  if (id > 101 && queues[0].getServiceCurve().getRate() != 1e9) {
    return false;
  }
  for (int i = 1; i < numQueues; i++) {
    auto higherS = queues[i-1].getServiceCurve();
    auto higherA = queues[i-1].getArrivalCurve();
    auto expected = higherS - higherA;

    auto lowerS = queues[i].getServiceCurve();
    if (higherS.getRate() < lowerS.getRate()) {
      return false;
    }
    if (expected.getRate() != lowerS.getRate() || expected.getB() != lowerS.getB()) {
      return false;
    }
  }
  return true;
}

void SimplePredictablePort::printQueueStates() const {
  EV_INFO << "Queue states:\n";
  for (int i = 0; i < queues.size(); i++) {
    EV_INFO << i << ": " << queues[i].getArrivalCurve() << "\n";
    EV_INFO << i << ": " << queues[i].getServiceCurve() << "\n";
    EV_INFO << i << ": " << queues[i].getQueueingDelayBound() << "\n";
    EV_INFO << i << ": " << queues[i].getBufferSizeBound() << "\n";
  }
}

std::vector<QueueInfo> SimplePredictablePort::getQueueStates() {
  std::vector<QueueInfo> queueStates;
  for (int i = 0; i < numQueues; i++) {
    const auto& curve = queues[i].getArrivalCurve();
    QueueInfo q;
    q.burst = curve.getBurst();
    q.rate = curve.getRate();

    queueStates.push_back(q);
  }
  return queueStates;
}

}