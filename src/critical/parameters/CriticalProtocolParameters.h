#ifndef _CRITICAL_PROTOCOLPARAMETERS_H
#define _CRITICAL_PROTOCOLPARAMETERS_H

#include <string>

namespace critical {

enum RoutingProtocol {
  LINK_STATE,
  PROBING
};

enum BudgetAllocator {
  CHAMELEON,
  CUSTOM
};

enum LsAlgorithm {
  MIN_DELAY,
  LARAC
};

enum LsUpdateStrategy {
  TIMED,
  CONSUMPTION,
  HYBRID
};

enum ProbingVariant {
  BREADTH_FIRST,
  DEPTH_FIRST
};

enum ProbingQueueHeuristic {
  GREEDY,
  HONEST,
  RANDOM
};

struct CriticalProtocolParameters {
  // The routing protocol to use, either probing or link-state
  RoutingProtocol routingProtocol;

  // The percentage of the bandwidth of every link that is reserved to the protocol flow
  double protocolBwUsage;

  // The protocol burst usage of the protocol flow in bytes 
  int protocolBurstUsage;

  // The queue to allocate the protocol flow into
  int protocolQueue;

  // Method of allocating budgets
  BudgetAllocator budgetAllocator;

  // The total number of queues to use. 1 Queue will be used for best-effort traffic
  int numQueues;

  // LS: the algorithm to compute paths
  LsAlgorithm lsAlgorithm;

  // LS: the consumption threshold to send updates if 'lsUpdate' is "consumption"
  double lsConsumptionThresh;

  // LS: the method to send out QoSLSAs
  LsUpdateStrategy lsUpdateStrategy;

  // LS: the interval to send QoSLSAs if 'lsUpdate' is "timed"
  double lsUpdateInterval;

  // Probing: the variant to use, either depth-first or breadth-first
  ProbingVariant probingVariant;

  // Probing: the queueing strategy to use, either greedy, honest, or random
  ProbingQueueHeuristic probingQueueHeuristic;

  // Probing: enable fast pruning
  bool probingFastPrune;
};

}

#endif 