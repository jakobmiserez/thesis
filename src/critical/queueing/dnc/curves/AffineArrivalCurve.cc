#include "AffineArrivalCurve.h"

#include <omnetpp.h>

namespace critical {

AffineArrivalCurve::AffineArrivalCurve(double rate, double burst) 
: DncCurve(CurveType::ArrivalCurve, rate, burst) {
  ASSERT(rate >= 0);
  ASSERT(burst >= 0);
}

AffineArrivalCurve::~AffineArrivalCurve() {

}

double AffineArrivalCurve::getRate() const {
  return a;
}

double AffineArrivalCurve::getBurst() const {
  return b;
}

AffineArrivalCurve& AffineArrivalCurve::operator+=(const AffineArrivalCurve& other) {
  a += other.a;
  b += other.b;
  ASSERT(a >= 0);
  ASSERT(b >= 0);
  return *this;
}

AffineArrivalCurve& AffineArrivalCurve::operator-=(const AffineArrivalCurve& other) {
  a -= other.a;
  b -= other.b;
  ASSERT(a >= 0);
  ASSERT(b >= 0);
  return *this;
}

AffineArrivalCurve AffineArrivalCurve::operator+(const AffineArrivalCurve& other) const {
  double newA = a + other.a;
  double newB = b + other.b;
  return AffineArrivalCurve(newA, newB);
}

}