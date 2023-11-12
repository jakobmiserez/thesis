#ifndef _CRITICAL_LSAOPT_H
#define _CRITICAL_LSAOPT_H

#include <omnetpp.h>
#include <inet/common/InitStages.h>
#include <vector>


using namespace omnetpp;

namespace critical {

class CriticalProtocol;

namespace ls {
    class LsaPacket;
    class MinimalLsRouter;
}

class LsaOptimizer: public cSimpleModule {
private:
    cMessage* timer;
    simtime_t startTime;
    std::vector<ls::MinimalLsRouter*> routers;
public:
    virtual ~LsaOptimizer();

protected:
    virtual int numInitStages() const override { return inet::NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage* msg) override;

private:
    void findProtocols();
};

}

#endif