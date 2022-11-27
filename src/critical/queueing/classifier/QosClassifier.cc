#include "QosClassifier.h"
#include "QosQueueReq_m.h"

namespace critical {

Define_Module(QosClassifier);

int QosClassifier::classifyPacket(inet::Packet* packet) {
  // Set default queue to the last queue 
  int queue = outputGates.size() - 1;

  const QosQueueReq* req = packet->removeTagIfPresent<QosQueueReq>();
  if (req != nullptr) {
    queue = req->getQueue();
    delete req;
    EV_INFO << "Classified packet to queue " << queue << " upon request\n";

    if (queue < 0 || queue >= outputGates.size()) {
      throw cRuntimeError("Queue request out of range");
    }
  }
  else {
    EV_INFO << "Classified packet to queue " << queue << " by default\n";
  }
  return queue;
}

}