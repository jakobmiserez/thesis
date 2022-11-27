#ifndef _CRITICAL_LS_METAACCESSCONTROL_H
#define _CRITICAL_LS_METAACCESSCONTROL_H

#include "critical/protocols/ls/topology/Topology.h"
#include <initializer_list>

namespace critical {

namespace ls {


template <class T>
class And: public Topology::PathAccessControl<T> {
  private:
    std::vector<Topology::PathAccessControl<Empty>*> empties;
    Topology::PathAccessControl<T>* data;

  public:
    And(Topology::PathAccessControl<T>* data, std::initializer_list<Topology::PathAccessControl<Empty>*> empties): data(data) {
      this->empties.insert(this->empties.end(), empties);
    };

    virtual ~And() {};

    virtual bool canAccessLink(const Topology::Link& link, const Topology::QueuedNode<T>& node) const override {
      if (!data->canAccessLink(link, node)) {
        return false;
      }

      // Fake object
      Topology::QueuedNode<Empty> empty;
      empty.metric = node.metric;
      empty.node = node.node;

      int i = 0;
      while (i < empties.size() && empties[i]->canAccessLink(link, empty)) {
        i++;
      }
      return i == empties.size();
    };

    virtual T updateAfterAccess(const Topology::Link& link, const Topology::QueuedNode<T>& node) const override {
      return data->updateAfterAccess(link, node);
    };

};

}

}


#endif 