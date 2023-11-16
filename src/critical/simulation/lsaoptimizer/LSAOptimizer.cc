#include "LSAOptimizer.h"

#include "critical/CriticalProtocol.h"
#include "critical/protocols/ls/minimal/MinimalLsRouter.h"

namespace critical {

Register_Class(LsaOptimizer);

LsaOptimizer::~LsaOptimizer() {
    cancelAndDelete(timer);
}

void LsaOptimizer::initialize(int stage) {

    if (stage == inet::INITSTAGE_APPLICATION_LAYER) {
        startTime = par("startTime");
        timer = new cMessage("Scheduler timer");
        timer->setKind(0);

        if (par("enabled").boolValue()) {
            scheduleAt(startTime < simTime() ? simTime() : startTime, timer);
        }
    }
}
    
void LsaOptimizer::handleMessage(cMessage* msg) {
    if (msg != timer) {
        return;
    }

    findProtocols();

    for (int i = 0; i < routers.size(); i++) {
        ls::MinimalLsRouter* router = routers[i];
        inet::Packet* packet = router->getPacketCreator().createLsa();

        const ls::LsaPacket* data = packet->peekAtFront<ls::LsaPacket>().get();

        for (int j = 0; j < i; j++) {
            routers[j]->getLSAs().insertLsa(data);
        }
        for (int j = i + 1; j < routers.size(); j++) {
            routers[j]->getLSAs().insertLsa(data);
        }
        delete packet;
    }

    routers.clear();
}

void LsaOptimizer::findProtocols() {
    for (int id = 0; id < getSimulation()->getLastComponentId(); id++) {
        cModule* mod = getSimulation()->getModule(id);
        if (mod && mod->getProperties()->get("criticalProtocol")) {
            CriticalProtocol* p = check_and_cast<CriticalProtocol*>(mod);
            ls::MinimalLsRouter* router = check_and_cast<ls::MinimalLsRouter*>(p->getRouter());
            routers.push_back(router);
        }
    }
}

}