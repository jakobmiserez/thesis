import inet.networklayer.contract.ipv6.Ipv6Address;
import inet.common.packet.chunk.Chunk;

namespace critical;

enum FlowPacketType {
  FLOW_REQUEST = 1;
  FLOW_RESPONSE = 2;
  FLOW_FREE = 3;
  FLOW_INTERRUPTED = 4;
};

class FlowRequestPacketBase extends inet::FieldsChunk {
  chunkLength = inet::B(1);

  inet::Ipv6Address source;
  inet::Ipv6Address destination;
  uint32_t label;

  FlowPacketType type = static_cast<FlowPacketType>(-1); // 1 byte
}

class FlowRequestPacket extends FlowRequestPacketBase {
  type = FLOW_REQUEST;

  uint64_t burst;                //  8B
  uint64_t bandwidth;            //  8B
  uint64_t delay;                //  8B

  chunkLength = inet::B(61);
}

class FlowResponsePacket extends FlowRequestPacketBase {
  type = FLOW_RESPONSE;

  bool accepted;

  chunkLength = inet::B(38);
}

class FlowFreePacket extends FlowRequestPacketBase {
  type = FLOW_FREE;

  chunkLength = inet::B(37);
}

class FlowInterruptedPacket extends FlowRequestPacketBase {
  type = FLOW_INTERRUPTED;

  bool continued;

  chunkLength = inet::B(38);
}

