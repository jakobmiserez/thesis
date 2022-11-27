#ifndef _CRITICAL_ROUTEE_H
#define _CRITICAL_ROUTEE_H

#include <inet/networklayer/common/L3Address.h>
#include <inet/networklayer/contract/IRoute.h>
#include "critical/common/util/Util.h"

namespace critical {

struct Route {
  int interface;
  double cost;

  Route(int interface, double cost): interface(interface), cost(cost) {};

  int estimatedHopsLeft(double accumulatedCost, double accumulatedHops) const {
    double costPerHop = accumulatedCost / accumulatedHops;
    return ceil(cost / costPerHop);
  };

  bool isViable() const {
    return cost != INF;
  };

  static Route from(inet::IRoute* route) {
    return Route(route->getInterface()->getInterfaceId(), route->getMetric());
  };

};

}


#endif 