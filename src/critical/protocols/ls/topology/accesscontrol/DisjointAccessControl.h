#ifndef _CRITICAL_LS_DISJOINTACCESSCONTROL_H
#define _CRITICAL_LS_DISJOINTACCESSCONTROL_H

#include "critical/protocols/ls/topology/Topology.h"
#include "critical/common/util/Util.h"

namespace critical {

namespace ls {

class DisjointAccessControl: public Topology::PathAccessControl<Empty> {
  private:
    std::set<RouterId> blackList;

  public:
    DisjointAccessControl(std::set<RouterId> blackList = {}): blackList(blackList) {};
    virtual ~DisjointAccessControl() {};

    void add(const RouterId& routerId) {
      blackList.insert(routerId);
    };

    virtual bool canAccessLink(const Topology::Link& link, const Topology::QueuedNode<Empty>& node) const override {
      return !contains(blackList, link.getTo()->getRouterId());
    };

    virtual Empty updateAfterAccess(const Topology::Link& link, const Topology::QueuedNode<Empty>& node) const override {
      return node.params;
    };

};

}

}

#endif 