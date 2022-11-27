import critical.common.packet.CriticalPacketBase;

import inet.networklayer.contract.ipv6.Ipv6Address;
cplusplus{{
  #include "critical/protocols/ls/topology/QueueLevelTopologyLinkEncoding.h"
}}


namespace critical::ls;

struct QueueLevelTopologyLinkEncoding::DecodedLink {
  @existingClass;
};

class LsPacketBase extends CriticalPacketBase {
  // Type = 1B
};

class LsPacketBaseId extends LsPacketBase {
  inet::Ipv6Address routerId;  // 17 B
};

class LsHelloPacket extends LsPacketBaseId {
  type = LS_HELLO;  // 17 bytes

  chunkLength = inet::B(17);
};


class LinkStateNetworkEntry extends inet::FieldsChunk {
  inet::Ipv6Address network;  // 16 bytes 
  uint8_t prefixLength;       // 1 byte
  uint8_t numQueues;          // 1 byte
  int linkId;                 // 2 bytes 

  chunkLength = inet::B(20);
}

class LinkStateNeighborEntry extends LinkStateNetworkEntry {
  // base: 20 bytes

  inet::Ipv6Address neighborId; // 16 bytes 
  uint8_t cost = 1; // 1 byte

  uint64_t bw;    // 8 bytes
  uint64_t delay; // 8 bytes 

  chunkLength = inet::B(53);
}

class LsaPacket extends LsPacketBaseId {
  type = LS_LSA;                        // 17 bytes 

  uint8_t networkEntriesCount;              // 1 byte 
  uint32_t sequenceNumber;                  // 4 byte
  LinkStateNetworkEntry networkEntries[];   // length * 20B
  LinkStateNeighborEntry neighborEntries[]; // length * 53B 

  chunkLength = inet::B(22); // DONT FORGET TO ADD  x * 20B + y * 53B
}

class QosLsaPacket extends LsPacketBaseId {
  type = LS_QOS_LSA;    // 17 bytes 
  uint32_t sequenceNumber;  // 4 bytes

  int linkId;               // 2 bytes 

  QueueInfo queues[];       // 16B * length

  chunkLength = inet::B(23); // DONT FORGET TO ADD  16B * length
}

class LsEmbedPacket extends LsPacketBaseId {
  type = LS_EMBED;      // 17B

  critical::Flow flow;  // 60 B
  uint32_t hop;         // 4B
  QueueLevelTopologyLinkEncoding::DecodedLink path[];  // 4 B * length

  chunkLength = inet::B(81); // DONT FORGET TO ADD 4B * length
}

class LsEmbedConfirmPacket extends LsPacketBase {
  type = LS_EMBED_CONFIRM; // 1B 

  critical::FlowId flow; // 36 B 

  chunkLength = inet::B(37);
}

class LsEmbedFailPacket extends LsPacketBaseId {
  type = LS_EMBED_FAIL; // 17 B 

  critical::FlowId flow; // 36 B 

  chunkLength = inet::B(53);
}