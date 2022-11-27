#ifndef CRITICAL_QOS_CLASSIFIER_H
#define CRITICAL_QOS_CLASSIFIER_H

#include <inet/queueing/base/PacketClassifierBase.h>

using namespace omnetpp;

namespace critical {

class QosClassifier : public inet::queueing::PacketClassifierBase {
  protected:
    virtual int classifyPacket(inet::Packet* packet) override;
};

}

#endif