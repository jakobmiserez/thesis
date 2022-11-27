import critical.common.packet.CriticalPacketBase;

import inet.networklayer.contract.ipv6.Ipv6Address;

namespace critical::probing;

class ProbingPacketBase extends CriticalPacketBase {
  // Type = 1 byte

  critical::FlowId flow; // 36 B

  chunkLength = inet::B(37);
}

class FlowPrunePacket extends ProbingPacketBase {
  type = PROBE_PRUNE;

  chunkLength = inet::B(38);
}

struct FlowProbeStats {
  // basic statistics for the probing mechanism
  uint64_t accumulatedDelay; // 8 bytes 
  uint32_t hops;             // 4 bytes
  uint32_t totalHopEstimate; // 4 bytes
}

class FlowProbePacket extends ProbingPacketBase {
  type = PROBE_PROBE;

  critical::FlowParameters params; // 24 bytes 

  FlowProbeStats stats; // 16 bytes 

  chunkLength = inet::B(77);
}

class FlowConfirmPacket extends ProbingPacketBase {
  type = PROBE_CONFIRM;
}

class FlowFreePacket extends ProbingPacketBase {
  type = PROBE_FREE;
}

class FlowFreeFailurePacket extends ProbingPacketBase {
  type = PROBE_FREE_FAILURE;
}
