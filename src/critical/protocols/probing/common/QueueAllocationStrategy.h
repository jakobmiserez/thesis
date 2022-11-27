#ifndef _CRITICAL_QUEUEALLOCATIONSTRATEGY_H
#define _CRITICAL_QUEUEALLOCATIONSTRATEGY_H

#include "critical/queueing/dnc/PredictablePort.h"
#include "critical/protocols/probing/packets/ProbingPackets_m.h"
#include "critical/common/routing/Route.h"

#include <optional>

namespace critical {

namespace probing {

class QueueAllocationStrategy {
  private:
    ProbingQueueHeuristic strategy;

  public:
    QueueAllocationStrategy(ProbingQueueHeuristic heuristic);
    virtual ~QueueAllocationStrategy();

    Link chooseQueue(PredictablePort* port, const FlowProbePacket* probe, const Route& route) const;

  private:
    Link chooseQueueGreedy(const std::vector<Link>& links) const;
    Link chooseQueueHonest(const std::vector<Link>& links, const FlowProbePacket* probe, const Route& route) const;
    Link chooseQueueRandom(const std::vector<Link>& links) const;
};

}

}



#endif