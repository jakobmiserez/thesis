#ifndef _CRITICAL_DNC_CURVE_H
#define _CRITICAL_DNC_CURVE_H

namespace critical {

/**
 * @brief The base class for a Deterministic Network Calculus (DNC) curve. 
 * The curves that can be modeled using this class are linear functions y = a*x + b. 
 */
class DncCurve {
  public:
    enum CurveType {
      ArrivalCurve = 1,
      ServiceCurve = 2
    };

  protected:
    CurveType type;
    double a;
    double b;

  protected:
    DncCurve(CurveType type, double a, double b);
    virtual ~DncCurve();

  public:
    double getType() const { return type; };
    double getA() const { return a; };
    double getB() const { return b; };

    double operator()(double t) const;
    double solveForT(double d) const;
};

}


#endif