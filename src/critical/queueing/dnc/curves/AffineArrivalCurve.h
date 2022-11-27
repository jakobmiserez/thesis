#ifndef _CRITICAL_AFFINE_ARRIVAL_CURVE_H
#define _CRITICAL_AFFINE_ARRIVAL_CURVE_H

#include "DncCurve.h"
#include <ostream>

namespace critical {

class AffineArrivalCurve : public DncCurve {

  public:
    AffineArrivalCurve(double rate, double burst);
    ~AffineArrivalCurve();

    double getRate() const;
    double getBurst() const;

    AffineArrivalCurve& operator+=(const AffineArrivalCurve& other);
    AffineArrivalCurve& operator-=(const AffineArrivalCurve& other);
    AffineArrivalCurve operator+(const AffineArrivalCurve& other) const;

    friend std::ostream& operator<<(std::ostream& os, const critical::AffineArrivalCurve& curve);
};

inline std::ostream& operator<<(std::ostream& os, const critical::AffineArrivalCurve& curve) {
  os << "AffineArrivalCurve(" << curve.getBurst() << "," << curve.getRate() << ")";
  return os;
};

}



#endif 