#ifndef _CRITICAL_LS_NETWORKTOPOLOGY_H
#define _CRITICAL_LS_NETWORKTOPOLOGY_H

#include "critical/protocols/ls/topology/Topology.h"

namespace critical {

namespace ls {

class LsaDatabase;

class NetworkTopology: public Topology {
  private:
    inet::Ipv6Address lastDestinationAddress = inet::Ipv6Address::UNSPECIFIED_ADDRESS;
  
  public:
    virtual ~NetworkTopology() {};

    void build(const LsaDatabase& lsas);

    void computeDistances(const RouterId& from);

    void computeAlternatives(const RouterId& from, const inet::Ipv6Address& dest);

    double getAlternativeRouteCost(const RouterId& from, const inet::Ipv6Address& dest, const RouterId& through);
};

}

}

#endif 