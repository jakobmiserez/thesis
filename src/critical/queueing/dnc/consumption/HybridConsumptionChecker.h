#ifndef _CRITICAL_HYBRIDCONSUMPTIONCHECKER_H
#define _CRITICAL_HYBRIDCONSUMPTIONCHECKER_H

namespace critical {

class HybridConsumptionChecker {
  private:
    double lastUpdate;
    double consumption;
    double thresh;
    double total;

  public:
    HybridConsumptionChecker();
    ~HybridConsumptionChecker();

    void init(double total, double threshPercentage);

    bool addConsumption(double consumption);

    bool removeConsumption(double consumption);

    void onTimeBasedUpdate();

    double getRelativeConsumption() const { return consumption / total; };
    double getAbsoluteConsumption() const { return consumption; };
    double getMax() const {
      return total;
    };
};

}


#endif