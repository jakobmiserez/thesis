#ifndef _CRITICAL_BFSTATES_H
#define _CRITICAL_BFSTATES_H

#include <inet/common/packet/Packet.h>

#include "critical/queueing/dnc/PredictablePort.h"

#include <list>

namespace critical {

namespace probing {

struct BfState {
  FlowId flow;
  FlowParameters params;

  std::list<inet::Packet*> queue;
  std::map<int, int> unconfirmedProbes;
  int interfaceId = -1;
  bool isFirstHop = false;

  BfState(FlowId flow): flow(flow) {};

  void clearAndDeleteQueue() {
    for (auto packet: queue) {
      delete packet;
    }
    queue.clear();
  }
};

}

}


#endif 