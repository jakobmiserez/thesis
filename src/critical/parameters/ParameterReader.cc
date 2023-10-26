#include "ParameterReader.h"

namespace critical {

CriticalProtocolParameters ParameterReader::readParams(cModule* protocol) {
  CriticalProtocolParameters params;
  this->protocol = protocol;
  params.routingProtocol = getRoutingProtocol();
  params.budgetAllocator = getAllocater();
  params.numQueues = protocol->getParentModule()->par("numQueues").intValue();
  params.protocolBwUsage =  par("protocolBwUsage").doubleValue();
  params.protocolBurstUsage = ((uint64_t)par("protocolBurstUsage").intValue()) * (uint64_t)8;
  params.protocolQueue = par("protocolQueue").intValue();

  
  params.probingVariant = getProbingVariant();
  params.probingQueueHeuristic = getProbingQueueHeuristic();
  params.probingFastPrune = par("probingFastPrune").boolValue();

  params.lsAlgorithm = getLsAlgorithm();
  params.lsUpdateStrategy = getLsUpdateStrategy();
  params.lsConsumptionThresh = par("lsConsumptionThresh").doubleValue();
  params.lsUpdateInterval = par("lsUpdateInterval").doubleValue();

  validateParams(params);
  return params;
}

void ParameterReader::validateParams(const CriticalProtocolParameters& params) {
  if (params.protocolBwUsage < 0 || params.protocolBwUsage > 1.0) {
    throw cRuntimeError("Invalid bw usage parameter: %f", params.protocolBwUsage);
  }

  if (params.lsConsumptionThresh <= 0 || params.lsConsumptionThresh > 1.0) {
    throw cRuntimeError("Invalid ls consumption thresh parameter: %f", params.lsConsumptionThresh);
  }

  if (params.lsUpdateInterval < 0) {
    throw cRuntimeError("Invalid ls update interval: %f", params.lsUpdateInterval);
  }
}

RoutingProtocol ParameterReader::getRoutingProtocol() {
  const auto& strValue = par("routingProtocol").stdstringValue();
  if (strValue == "ls")
    return RoutingProtocol::LINK_STATE;
  if (strValue == "probing")
    return RoutingProtocol::PROBING;
  throw cRuntimeError("Unknown routing protocol: %s", strValue.c_str());
}
    
BudgetAllocator ParameterReader::getAllocater() {
  const auto& strValue = par("budgetAllocator").stdstringValue();
  if (strValue == "chameleon")
    return BudgetAllocator::CHAMELEON;
  if (strValue == "custom")
    return BudgetAllocator::CUSTOM;
  if (strValue == "exp_100_100_2")
    return BudgetAllocator::EXP_DIFF_100_100_2;

  if (strValue == "lin_100_200_100")
    return BudgetAllocator::LINEAR_DIFF_100_200_100;
  if (strValue == "lin_100_400_200")
    return BudgetAllocator::LINEAR_DIFF_100_400_200;
  
  if (strValue == "const_100_500")
    return BudgetAllocator::CONSTANT_DIFF_100_500;
  if (strValue == "const_500_500")
    return BudgetAllocator::CONSTANT_DIFF_500_500;
  if (strValue == "const_500_0")
    return BudgetAllocator::CONSTANT_DIFF_500_0;

  throw cRuntimeError("Unknown allocator strategy: %s", strValue.c_str());
}
    
LsAlgorithm ParameterReader::getLsAlgorithm() {
  const auto& strValue = par("lsAlgorithm").stdstringValue();
  if (strValue == "larac")
    return LsAlgorithm::LARAC;
  if (strValue == "mindelay")
    return LsAlgorithm::MIN_DELAY;
  throw cRuntimeError("Unknown algorithm: %s", strValue.c_str());
}
    
LsUpdateStrategy ParameterReader::getLsUpdateStrategy() {
  const auto& strValue = par("lsUpdateStrategy").stdstringValue();
  if (strValue == "timed")
    return LsUpdateStrategy::TIMED;
  if (strValue == "consumption")
    return LsUpdateStrategy::CONSUMPTION;
  if (strValue == "hybrid")
    return LsUpdateStrategy::HYBRID;
  throw cRuntimeError("Unknown update strategy: %s", strValue.c_str());
}

ProbingVariant ParameterReader::getProbingVariant() {
  const auto& strValue = par("probingVariant").stdstringValue();
  if (strValue == "bf")
    return ProbingVariant::BREADTH_FIRST;
  if (strValue == "df")
    return ProbingVariant::DEPTH_FIRST;
  throw cRuntimeError("Unknown probing variant: %s", strValue.c_str());
}

ProbingQueueHeuristic ParameterReader::getProbingQueueHeuristic() {
  const auto& strValue = par("probingQueueHeuristic").stdstringValue();
  if (strValue == "greedy")
    return ProbingQueueHeuristic::GREEDY;
  if (strValue == "honest")
    return ProbingQueueHeuristic::HONEST;
  if (strValue == "random")
    return ProbingQueueHeuristic::RANDOM;
  throw cRuntimeError("Unknown probing queue heuristic: %s", strValue.c_str());
}

}