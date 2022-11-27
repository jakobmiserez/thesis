#ifndef _CRITICAL_RATE_LATENCY_SERVICE_CURVE_H
#define _CRITICAL_RATE_LATENCY_SERVICE_CURVE_H

#include "DncCurve.h"
#include "AffineArrivalCurve.h"

#include <ostream>

namespace critical {

class RateLatencyServiceCurve : public DncCurve {
  private:
    double t0;

  public:
    RateLatencyServiceCurve(double rate, double b = 0);
    ~RateLatencyServiceCurve();

    double getT0() const { return t0; }
    double getRate() const { return a; }

    RateLatencyServiceCurve& operator>>(double shift);
    RateLatencyServiceCurve operator-(const AffineArrivalCurve& arrival) const;
    bool operator>(const AffineArrivalCurve& arrival) const;

    RateLatencyServiceCurve& shiftDown(double shift);

    friend std::ostream& operator<<(std::ostream& os, const critical::RateLatencyServiceCurve& curve);

  private:
    void recomputeT0();

};

inline std::ostream& operator<<(std::ostream& os, const critical::RateLatencyServiceCurve& curve) {
  os << "RateLatencyServiceCurve(" << curve.getT0() << "," << curve.getRate() << ")";
  return os;
};

}



#endif 