#ifndef _CRITICAL_QUEUELEVELTOPOLOGY_H
#define _CRITICAL_QUEUELEVELTOPOLOGY_H

#include "critical/protocols/ls/topology/Topology.h"
#include "critical/protocols/ls/topology/accesscontrol/QueueAccessControl.h"
#include "critical/protocols/ls/packets/LsPackets_m.h"
#include "QueueLevelTopologyLinkEncoding.h"


#include <optional>

namespace critical {

namespace ls {

class LsaDatabase;
class QosLsaDatabase;

class QueueLevelTopology: public Topology {
  private:
    struct PathParameters {
      std::vector<const Link*> path;
      double cost;
      double delay;
    };
  private: 
    QueueAccessControl accessControl;

  public:
    virtual ~QueueLevelTopology() {};

    void build(LsaDatabase& lsas, QosLsaDatabase& qos);

    std::optional<std::vector<const Link*>> larac(const RouterId& from, const Flow& flow, std::initializer_list<Topology::PathAccessControl<Empty>*> empties = {});
    
    /**
     * Performs Dijkstra on the queue-level topology with additional access control.
     **/
    std::optional<std::vector<const Link*>> mindelay(const RouterId& from, const Flow& flow, std::initializer_list<Topology::PathAccessControl<Empty>*> empties = {});

    /**
     * Performs Dijkstra on the queue-level topology without any access control.
     **/
    std::optional<std::vector<const Link*>> pureDijkstra(const RouterId& from, const Flow& flow);

    std::vector<const Link*> reconstructPath(const LsEmbedPacket* embedding) const;

  private:
    PathParameters computePathParameters(Node* dest);

    double recomputeCost(const std::vector<const Link*>& path, std::function<double(const Link&)> costf);
};

}

}

#endif 