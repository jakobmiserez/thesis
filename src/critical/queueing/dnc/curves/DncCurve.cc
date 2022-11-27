#include "DncCurve.h"

#include <math.h>

namespace critical {

DncCurve::DncCurve(CurveType type, double a, double b)
  : type(type), a(a), b(b) {

}

DncCurve::~DncCurve() {

}

double DncCurve::operator()(double t) const {
  return std::abs(a * t + b);
}

double DncCurve::solveForT(double d) const {
  return (d - b) / a; 
}

}