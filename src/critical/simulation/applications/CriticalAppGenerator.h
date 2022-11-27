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
    static const Application database;
    static const Application scada;
    static const Application production;
    static const Application control;
    static const Application video;
    static const Application datamining;
    static const Application other;

    static const std::vector<const Application*> apps;
      

  public:
    FlowParameters generateParameters(cRNG* rng);   
};

}


#endif 