#ifndef _CRITICAL_SCHEDULER_H
#define _CRITICAL_SCHEDULER_H

#include <omnetpp.h>
#include <inet/common/InitStages.h>
#include <set>
#include <string>
#include <vector>
#include <random>

#include "critical/flows/Flow.h"
#include "critical/simulation/applications/CriticalAppGenerator.h"

using namespace omnetpp;

namespace critical {

class Scheduler: public cSimpleModule {
  private:
    enum TimerKind { START, SCHEDULE };

    cMessage* timer = nullptr;
    simtime_t startTime;
    simtime_t duration;
    simtime_t interval;
    int flowsPerInterval;

    std::vector<cModule*> hosts;

    // Map that keeps track of the number of udp applications of every host
    std::map<cModule*, uint16_t> numUdpApps;
    uint32_t udpAppOffset = 4097;

    // Map that keeps track of the flow labels per flow that can be generated
    std::map<int, uint32_t> flowLabels;

    
    CriticalAppGenerator appGen;

    uint64_t scheduledFlows = 0;

    static simsignal_t flowConfiguredSignal;

  public:
    Scheduler();
    virtual ~Scheduler();

  protected:
    virtual int numInitStages() const override { return inet::NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage* msg) override;

  private:
    void findApplicationHosts();
    void scheduleFlows();
    std::pair<std::string, std::string> scheduleFlow();

    void connectUdpApplication(cModule* app, cModule* host);

    cModule* addUdpCriticalApplicationTo(
      cModule* host, 
      cModule* flowServerRouter, 
      uint16_t srcPort, 
      cModule* dest, 
      uint16_t destPort, 
      uint32_t flowLabel,
      const FlowParameters& params
    );

    int getUdpAppNumber(cModule* router);

    double computeFlowDuration();
    simtime_t computeInterval();

    cModule* addUdpSinkTo(cModule* router, uint16_t port);

    size_t indexOf(int i, int j) {
      return i * hosts.size() + j;
    };

    std::pair<size_t, size_t> indexOf2d(uint32_t index) {
      size_t i = index / hosts.size();
      size_t j = index % hosts.size();
      return std::make_pair(i, j);
    };
    
};

}

#endif