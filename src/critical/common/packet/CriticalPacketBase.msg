import inet.common.packet.chunk.Chunk;

cplusplus{{
  #include "critical/flows/Flow.h"
}}

struct critical::Flow {
  @existingClass;
}
struct critical::FlowId {
  @existingClass;
}
struct critical::FlowParameters {
  @existingClass;
}

namespace critical;

enum PacketType {
  PROBE_PROBE = 1;
  PROBE_PRUNE = 2;
  PROBE_CONFIRM = 3;
  PROBE_FREE = 4;
  PROBE_FREE_FAILURE = 5;

  LS_HELLO = 11;
  LS_LSA = 12;
  LS_QOS_LSA = 13;
  LS_EMBED = 14;
  LS_EMBED_CONFIRM = 15;
  LS_EMBED_FAIL =  16;
};

class CriticalPacketBase extends inet::FieldsChunk {
  PacketType type = static_cast<PacketType>(-1); // 1 byte 
};

struct QueueInfo {
  double burst;  // 8 bytes 
  double rate;   // 8 bytes 
  // 16 bytes
} 
