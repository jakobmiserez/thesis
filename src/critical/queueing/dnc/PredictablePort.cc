#include "PredictablePort.h"

#include "critical/queueing/dnc/curves/helpers.h"
#include "critical/flows/map/linear/LinearFlowMap.h"
#include "critical/queueing/Link.h"
#include "critical/common/util/ModuleHelpers.h"
#include "critical/CriticalProtocol.h"

namespace critical {

PredictablePort::PredictablePort(int id, int numQueues, CriticalProtocol* protocol)
: SimplePredictablePort(id, numQueues, protocol) {
  protocol->getFlowTable().addListener(this, ObservingPriority::HIGH);
}

PredictablePort::~PredictablePort() {
  protocol->getFlowTable().removeListener(this);
}

void PredictablePort::initialize(double linkRate) {
  initializing = true;
  consumptionChecker.init(linkRate, getParams().lsConsumptionThresh);
  SimplePredictablePort::initialize(linkRate);
  initializing = false;
}

std::vector<Link> PredictablePort::getPossibleLinks(
  const FlowParameters& params, 
  uint64_t accumulatedDelay
) {
  EV_INFO << "Finding possible links "<< "(link rate is "<< linkRate << " bps, delay is " << linkDelay << " us)\n";
  EV_INFO << params << "\n";
  std::vector<Link> res;

  auto predicate = [this, params, accumulatedDelay](PredictableQueue& queue) { 
    uint64_t delay = accumulatedDelay + queue.getDelayBudget() + getLinkDelay();
    return delay <= params.delay && canAllocateFlow(queue.getIndex(), params);
  };

  for (auto& queue: queues) {
    if (predicate(queue)) {
      res.emplace_back(this, queue.getIndex());
    }
  }

  return res;
}

FlowParameters PredictablePort::allocateFlow(int queue, const FlowParameters& params) {
  FlowParameters newParams = SimplePredictablePort::allocateFlow(queue, params);

  EV_INFO << "(PORT " << getId() << " ) " << "Allocating params: " << params << "\n";

  // Check the consumption
  if (consumptionChecker.addConsumption(params.dncModel().getRate()) && !initializing)
    notifyConsumptionChange(true, true);
  else 
    notifyConsumptionChange(false, true);

  ASSERT(check());
  return newParams;
}

void PredictablePort::freeFlow(int queue, const FlowParameters& params) {
  SimplePredictablePort::freeFlow(queue, params);

  // Check the consumption
  if (consumptionChecker.removeConsumption(params.dncModel().getRate()))
    notifyConsumptionChange(true, false);
  else 
    notifyConsumptionChange(false, false);
}

void PredictablePort::onFlowAccepted(const FlowTableEntry* entry) {
  if (entry->data.nextInterface == id) {
    registeredOutgoingFlows.insert(entry);
  }
  else if (entry->data.prevInterface == id) {
    registeredIncomingFlows.insert(entry);
  }
}

void PredictablePort::onFlowDelete(const FlowTableEntry* entry) {
  if (entry->data.nextInterface == id) {
    registeredOutgoingFlows.erase(entry);
  }
  else if (entry->data.prevInterface == id) {
    registeredIncomingFlows.erase(entry);
  }
}

void PredictablePort::notifyConsumptionChange(bool significant, bool up) {
  notifyListeners([this, significant, up](IConsumptionListener* l) { l->onConsumptionChange(id, significant, up); });
}

}