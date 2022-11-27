#ifndef _CRITICAL_CONSUMPTIONCHECKER_H
#define _CRITICAL_CONSUMPTIONCHECKER_H

namespace critical {

class ConsumptionChecker {
  private:
    double total;
    double consumption;

    double step;
    double previousThresh;
    double nextThresh;

  public:
    ConsumptionChecker();
    ~ConsumptionChecker();

    void init(double total, double threshPercentage);

    bool addConsumption(double consumption);

    bool removeConsumption(double consumption);

    double getRelativeConsumption() const { return consumption / total; };
    double getAbsoluteConsumption() const { return consumption; };
    double getMax() const {
      return total;
    };

  private:
    void logConsumption();
};

}


#endif