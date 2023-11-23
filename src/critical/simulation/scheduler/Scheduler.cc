#include "Scheduler.h"

#include "critical/common/util/ModuleHelpers.h"
#include "critical/simulation/recorder/FlowRecorderData.h"

#include <fstream>
#include <iostream>
#include <map>

namespace critical {

Register_Class(Scheduler);

simsignal_t Scheduler::flowConfiguredSignal = registerSignal("flowConfigured");


Scheduler::Scheduler() {

}

Scheduler::~Scheduler() {
  cancelAndDelete(timer);
}

void Scheduler::initialize(int stage) {
  if (stage == inet::INITSTAGE_APPLICATION_LAYER) {
    startTime = par("startTime");
    duration = par("duration");
    interval = par("interval");
    flowsPerInterval = par("flowsPerInterval").intValue();
    maxScheduledFlows = par("maxScheduledFlows").intValue();
    packetBurst = par("packetBurst").intValue();
    timer = new cMessage("Scheduler timer");
    timer->setKind(TimerKind::START);
    scheduleAt(startTime < simTime() ? simTime() : startTime, timer);
  }
}

void Scheduler::handleMessage(cMessage* msg) {
  if (msg == timer) {
    switch (msg->getKind()) {
      case TimerKind::START: {
        findApplicationHosts();
        timer->setKind(TimerKind::SCHEDULE);
        scheduleAt(simTime() + computeInterval(), timer);
      } break;
      case TimerKind::SCHEDULE:
      default: {
        scheduleFlows();
        if (duration.isZero() || simTime() < startTime + duration) {
          scheduleAt(simTime() + computeInterval(), timer);
        }
      } break;
    }
  }
}

void Scheduler::scheduleFlows() {
  if (!duration.isZero() && simTime() >= startTime + duration) {
    return;
  }
  
  std::vector<std::pair<std::string,std::string>> flows;
  flows.reserve(flowsPerInterval);
  for (int i = 0; i < flowsPerInterval; i++) {
    if (maxScheduledFlows > 0 && scheduledFlows > maxScheduledFlows) {
      continue;
    }
    scheduledFlows++;
    auto f = scheduleFlow();
    flows.push_back(f);
  } 
  for (auto& [src, dest]: flows) {
    EV_INFO << "Scheduled flow: " << src << " -> " << dest << "\n";
  }
}

std::pair<std::string, std::string> Scheduler::scheduleFlow() {
  auto rng = getRNG(0);

  auto host1 = rng->intRand(hosts.size());
  auto host2 = rng->intRand(hosts.size());

  if (host1 == host2) {
    return scheduleFlow();
  }

  cModule* src = hosts[host1];
  cModule* dest = hosts[host2];

  uint16_t sinkUdpPort = numUdpApps[dest]++ + udpAppOffset;
  uint16_t appUdpPort = numUdpApps[src]++ + udpAppOffset;
  uint32_t flowLabel = ++flowLabels[indexOf(host1, host2)];

  
  FlowParameters params = appGen.generateParameters(getRNG(0));
  cModule* source = addUdpCriticalApplicationTo(
    src, src->getParentModule()->getSubmodule("router"), appUdpPort, 
    dest, sinkUdpPort, flowLabel, params
  );
  cModule* sink = addUdpSinkTo(dest, sinkUdpPort);

  FlowRequirements req(params, source, sink);
  emit(flowConfiguredSignal, &req);

  return std::make_pair(src->getParentModule()->getName(), dest->getParentModule()->getName());
}

cModule* Scheduler::addUdpCriticalApplicationTo(
  cModule* host, 
  cModule* flowServerRouter, 
  uint16_t srcPort, 
  cModule* dest, 
  uint16_t destPort, 
  uint32_t flowLabel,
  const FlowParameters& params
) {
  cModuleType* type = cModuleType::get("critical.simulation.applications.CriticalUdpApp");

  std::string name("DynApp");
  name += std::to_string(getUdpAppNumber(host));

  cModule* app = type->create(name.c_str(), host);
  app->par("srcAddress") = host->getFullPath();
  app->par("flowServerAddress") = flowServerRouter->getFullPath();
  app->par("destAddress") = dest->getFullPath();
  app->par("port") = srcPort;
  app->par("destPort") = destPort;
  app->par("startTime") = -1.0;
  app->par("duration") = computeFlowDuration();
  app->par("delay") = params.delay;
  app->par("bandwidth") = params.rate;
  app->par("burst") = params.burst;
  
  // Generate random packet burst or use preconfigured for every flow
  if (packetBurst < 0)
    app->par("packetBurst") = getRNG(0)->intRand(4) + 1;
  else
    app->par("packetBurst") = packetBurst;

  app->par("label") = flowLabel;
  app->par("noTraffic") = par("noTraffic");
  app->par("noTrafficStop") = par("noTrafficStop");
  app->finalizeParameters();
  app->buildInside();

  connectUdpApplication(app, host);

  app->callInitialize();
  app->scheduleStart(simTime());

  return app;
}

cModule* Scheduler::addUdpSinkTo(cModule* host, uint16_t port) {
  cModuleType* type = cModuleType::get("inet.applications.udpapp.UdpSink");

  std::string name("DynSink");
  name += std::to_string(getUdpAppNumber(host));

  cModule* app = type->create(name.c_str(), host);
  app->par("localPort") = port;
  app->finalizeParameters();
  app->buildInside();

  connectUdpApplication(app, host); 

  app->callInitialize();
  app->scheduleStart(simTime());
  
  return app;
}

void Scheduler::connectUdpApplication(cModule* app, cModule* host) {
  cModule* udpConnect = host->getSubmodule("at");

  int inputGates = udpConnect->gate("in", 0)->getVectorSize();
  int outputGates = udpConnect->gate("out", 0)->getVectorSize();

  // resize gate sizes
  udpConnect->setGateSize("out", outputGates + 1);
  udpConnect->setGateSize("in", inputGates + 1);

  cGate* in = udpConnect->gate("in", inputGates);
  cGate* out = udpConnect->gate("out", outputGates);

  app->gate("socketOut")->connectTo(in);
  out->connectTo(app->gate("socketIn"));
}

int Scheduler::getUdpAppNumber(cModule* router) {
  return router->getSubmodule("at")->gate("out", 0)->getVectorSize();
}

double Scheduler::computeFlowDuration() {
  return 0;
} 
  
simtime_t Scheduler::computeInterval() {
  return interval;
}

void Scheduler::findApplicationHosts() {
  for (int id = 0; id < getSimulation()->getLastComponentId(); id++) {
    cModule* mod = getSimulation()->getModule(id);
    if (mod && mod->getProperties()->get("applicationHost")) {
      hosts.push_back(mod);
    }
  }
}

}

