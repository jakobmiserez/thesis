package critical.queueing.classifier;

import inet.queueing.base.PacketClassifierBase;
import inet.queueing.contract.IPacketClassifier;

simple QosClassifier extends PacketClassifierBase like IPacketClassifier {
  parameters:
    @class(critical::QosClassifier);
}
