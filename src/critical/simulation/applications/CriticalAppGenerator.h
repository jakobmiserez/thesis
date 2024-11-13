#ifndef _CRITICAL_APPGENERATOR_H
#define _CRITICAL_APPGENERATOR_H

#include "critical/flows/Flow.h"
#include <omnetpp.h>

using namespace omnetpp;

namespace critical {

inline unsigned long kb(unsigned long x) { return x * 1000; };
inline unsigned long mb(unsigned long x) { return x * 1000 * 1000; };

class Application {
  private:
    unsigned long rateMin;
    unsigned long rateMax;
    unsigned long burstMin;
    unsigned long burstMax;
    unsigned long delayMin;
    unsigned long delayMax;

  public:
    Application(
      unsigned long rateMin,
      unsigned long rateMax,
      unsigned long burstMin,
      unsigned long burstMax,
      unsigned long delayMin,
      unsigned long delayMax
    ): 
      rateMin(rateMin), rateMax(rateMax), 
      burstMin(burstMin), burstMax(burstMax), 
      delayMin(delayMin), delayMax(delayMax) {};

    FlowParameters generateParams(cRNG* rng) const {
      unsigned long rate = rateMin + rng->intRand(rateMax - rateMin);
      unsigned long burst = burstMin + rng->intRand(burstMax - burstMin);
      unsigned long delay = delayMin + rng->intRand(delayMax - delayMin);

      return FlowParameters(delay, rate, burst);
    };
};

class CriticalAppGenerator {
  public:
    enum AppDistribution {
      RANDOM = 0,
      VIDEO_40,
      VIDEO_60,
      VIDEO_80,
      VIDEO_100,
      DB_40,
      DB_60,
      DB_80,
      DB_100,
      PROD_40,
      PROD_60,
      PROD_80,
      PROD_100,

      APP_DISTRIBUTION_COUNT
    };

    static AppDistribution parseAppDistribution(const std::string& appDistributionStr) {
      if (appDistributionStr == "random")
        return RANDOM;
      if (appDistributionStr == "video40")
        return VIDEO_40;
      if (appDistributionStr == "video60")
        return VIDEO_60;
      if (appDistributionStr == "video80")
        return VIDEO_80;
      if (appDistributionStr == "video100")
        return VIDEO_100;
      if (appDistributionStr == "db40")
        return DB_40;
      if (appDistributionStr == "db60")
        return DB_60;
      if (appDistributionStr == "db80")
        return DB_80;
      if (appDistributionStr == "db100")
        return DB_100;
      if (appDistributionStr == "prod40")
        return PROD_40;
      if (appDistributionStr == "prod60")
        return PROD_60;
      if (appDistributionStr == "prod80")
        return PROD_80;
      if (appDistributionStr == "prod100")
        return PROD_100;
      throw omnetpp::cRuntimeError("Unknown AppDistribution: %s", appDistributionStr.c_str());
    }

    static const Application database;
    static const Application scada;
    static const Application production;
    static const Application control;
    static const Application video;
    static const Application datamining;
    static const Application other;

    static const std::vector<const Application*> apps;
    
    static const std::array<std::array<uint8_t, 5>, APP_DISTRIBUTION_COUNT> distributionWeights;
      

  public:
    CriticalAppGenerator();

    void setAppDistribution(AppDistribution appDistribution) {
      this->appDistribution = appDistribution;
      setupHistogram();
    };

    FlowParameters generateParameters(cRNG* rng);

  private:
    void setupHistogram();

  private:
    AppDistribution appDistribution;
    omnetpp::cHistogram histogram;
};

}


#endif 