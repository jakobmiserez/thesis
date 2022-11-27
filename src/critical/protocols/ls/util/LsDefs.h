#ifndef _CRITICAL_LS_DEFS_H
#define _CRITICAL_LS_DEFS_H

#include <inet/networklayer/contract/ipv6/Ipv6Address.h>
#include "critical/protocols/ls/packets/LsPackets_m.h"

namespace critical {

namespace ls {

typedef inet::Ipv6Address RouterId;

struct Link {
  inet::Ipv6Address networkAddress;
  uint8_t prefixLength;
  int linkId;
  int numQueues;
  
  uint64_t delay;
  uint64_t bw;
};

struct RouterNeighborLink: public Link {
  RouterId to;
  uint8_t cost;
};

struct QosLinkInfo {
  int linkId;
  uint32_t sequenceNumber;
  std::vector<QueueInfo> queues;

  QosLinkInfo() {};
  QosLinkInfo(int numQueues) {
    queues.reserve(numQueues);
    for (int i = 0; i < numQueues; i++) {
      QueueInfo q;
      q.burst = 0;
      q.rate = 0;
      queues.push_back(q);
    }
  }
};

}

}



#endif 