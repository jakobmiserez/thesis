#ifndef _CRITICAL_PROTOCOLPARAMETERS_H
#define _CRITICAL_PROTOCOLPARAMETERS_H

#include <string>

namespace critical {

enum RoutingProtocol {
  LINK_STATE,
  PROBING
};

enum BudgetAllocator {
  CUSTOM = 0,
  CHAMELEON,
  CONST1,
  EXP,
  GAP,
  INCREASING1,
  INCREASING2,
  SIMPLE1,
  SIMPLE2,
  SIMPLE3,
  



  CONSTANT_DIFF_50_100,
  CONSTANT_DIFF_50_200,
  CONSTANT_DIFF_100_500,
  CONSTANT_DIFF_500_500,
  CONSTANT_DIFF_100_0,
  CONSTANT_DIFF_500_0,
  CONSTANT_DIFF_1000_0,
  
  LINEAR_DIFF_100_200_100,
  LINEAR_DIFF_100_400_200,
  
  EXP_DIFF_100_100_2,
  
  LOG_DIFF,

  QUADRATIC_DIFF


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
  
  bool recordMemoryFootprint;
  bool recordQueueStates;
  bool recordConsumption;

  // Optimization shortcuts
  bool optimizeMemoryFootprintRecording;
  bool optimizeLsas;
};

}

#endif 