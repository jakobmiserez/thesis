#include "RateLatencyServiceCurve.h"

#include <omnetpp.h>

namespace critical {

RateLatencyServiceCurve::RateLatencyServiceCurve(double rate, double b)
: DncCurve(CurveType::ServiceCurve, rate, b) {
  recomputeT0();
}

RateLatencyServiceCurve::~RateLatencyServiceCurve() {

}

RateLatencyServiceCurve& RateLatencyServiceCurve::operator>>(double shift) {
  b -= shift * a;
  recomputeT0();
  return *this;
}

RateLatencyServiceCurve RateLatencyServiceCurve::operator-(const AffineArrivalCurve& arrival) const {
  double rate = a - arrival.getA();
  double newB = b - arrival.getB();

  return RateLatencyServiceCurve(rate, newB);
}

bool RateLatencyServiceCurve::operator>(const AffineArrivalCurve& arrival) const {
  return a > arrival.getA();
}

void RateLatencyServiceCurve::recomputeT0() {
  ASSERT(a >= 0);
  if (a == 0) 
    t0 = 0;
  else 
    t0 = -b / a;
  ASSERT(t0 >= 0);
}

RateLatencyServiceCurve& RateLatencyServiceCurve::shiftDown(double shift) {
  b -= shift;
  recomputeT0();
  return *this;
}

}