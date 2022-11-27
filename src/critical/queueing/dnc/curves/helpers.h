#ifndef _CRITICAL_CURVE_HELPERS_H
#define _CRITICAL_CURVE_HELPERS_H

#include "AffineArrivalCurve.h"
#include "RateLatencyServiceCurve.h"

#include "critical/common/util/Util.h"

namespace critical {

/**
 * @brief Returns the horizontal deviation in seconds between the arrival and service curve
 * 
 * @param arrival 
 * @param service 
 * @return double 
 */
double inline horizontalDeviation(const AffineArrivalCurve& arrival, const RateLatencyServiceCurve& service) {
  ASSERT(arrival.getRate() >= 0);
  ASSERT(service.getRate() > 0);

  if (arrival.getRate() >= service.getRate()) {
    return INF;
  }

  return service.solveForT(arrival.getBurst());
};

/**
 * @brief Returns the horizontal deviation in bits between the arrival and service curve
 * 
 * @param arrival 
 * @param service 
 * @return double 
 */
double inline verticalDeviation(const AffineArrivalCurve& arrival, const RateLatencyServiceCurve& service) {
  ASSERT(arrival.getRate() >= 0);
  ASSERT(service.getRate() > 0);

  if (arrival.getRate() >= service.getRate()) {
    return INF;
  }

  return arrival(service.getT0());
};

}

#endif 