#ifndef _CRITICAL_DFBFSTATES_H
#define _CRITICAL_DFBFSTATES_H

#include "critical/protocols/probing/packets/ProbingPackets_m.h"

namespace critical {

namespace probing {

struct DfState {
  FlowId flow;
  FlowParameters params;
  std::set<int> triedInterfaces;
  int incomingInterface = -1;
  bool isFirstHop = false;
  FlowProbePacket* probe = nullptr;

  int outgoingInterface = -1;
  int queue = -1;

  DfState(const FlowId& flow) : flow(flow) {};
};

}

}

#endif 