#ifndef _CRITICAL_LS_QUEUEACCESSCONTROL_H
#define _CRITICAL_LS_QUEUEACCESSCONTROL_H

#include "critical/protocols/ls/topology/Topology.h"
#include "critical/flows/Flow.h"
//#include "critical/protocols/ls/lsa/QueueStates.h"
#include "critical/protocols/ls/lsa/QosLsaDatabase.h"

namespace critical {

namespace ls {

class QueueAccessControl: public Topology::PathAccessControl<FlowParameters> {
  private:
    const QosLsaDatabase* qosLsaDatabase = nullptr;

  public:
    QueueAccessControl() {};
    virtual ~QueueAccessControl() {};

    void setQosLsaDatabase(const QosLsaDatabase* qosLsaDatabase) {
      this->qosLsaDatabase = qosLsaDatabase;
    };

    virtual bool canAccessLink(const Topology::Link& link, const Topology::QueuedNode<FlowParameters>& node) const override {
      int linkId = link.getId() / 16;
      int queue = link.getId() % 16;

      const FlowParameters& params = node.params;
      const auto& linkControl = qosLsaDatabase->getQueueStates(node.node->getRouterId(), linkId);

      return linkControl->canAllocateFlow(queue, params);
    };

    virtual FlowParameters updateAfterAccess(const Topology::Link& link, const Topology::QueuedNode<FlowParameters>& node) const override {
      int linkId = link.getId() / 16;
      int queue = link.getId() % 16;

      const FlowParameters& params = node.params;
      const auto& linkControl = qosLsaDatabase->getQueueStates(node.node->getRouterId(), linkId);

      return linkControl->updatedFlowParams(queue, params);
    };

};

}

}


#endif 