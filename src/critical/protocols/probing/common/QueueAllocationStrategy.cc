#include "QueueAllocationStrategy.h"

#include "critical/queueing/Link.h"
#include "critical/common/util/FuncList.h"

namespace critical {

namespace probing {

QueueAllocationStrategy::QueueAllocationStrategy(ProbingQueueHeuristic strategy)
: strategy(strategy) {

}

QueueAllocationStrategy::~QueueAllocationStrategy() {

}

Link QueueAllocationStrategy::chooseQueue(PredictablePort* port, const FlowProbePacket* probe, const Route& route) const {
  const FlowParameters& params = probe->getParams();

  std::vector<Link> links = port->getPossibleLinks(params, probe->getStats().accumulatedDelay);

  switch (strategy) {
    case HONEST:
      return chooseQueueHonest(links, probe, route);
    case GREEDY:
      return chooseQueueGreedy(links);
    case RANDOM:
    default:
      return chooseQueueRandom(links);
  }
}

Link QueueAllocationStrategy::chooseQueueGreedy(const std::vector<Link>& links) const {
  return links[0];
}

Link QueueAllocationStrategy::chooseQueueHonest(const std::vector<Link>& links, const FlowProbePacket* probe, const Route& route) const {
  uint32_t hops = probe->getStats().hops;
  uint32_t accumulatedDelay = probe->getStats().accumulatedDelay;

  double delayBudget = (double)probe->getParams().delay - (double)accumulatedDelay;
  double expectedHopsToGo = route.estimatedHopsLeft(hops, hops);
  double budgetPerHop = delayBudget / expectedHopsToGo;

  return FuncList<Link>::from(links)
    .sort([budgetPerHop](const Link& l1, const Link& l2) {
      double d1 = l1.getDelay();
      double d2 = l2.getDelay();
      if (d1 > budgetPerHop || d2 > budgetPerHop) {
        return d1 < d2;
      }
      return d1 > d2;
    })
    .first()
    .value();
}

Link QueueAllocationStrategy::chooseQueueRandom(const std::vector<Link>& links) const {
  int i = std::rand() % links.size();
  return links[i];
}

}

}