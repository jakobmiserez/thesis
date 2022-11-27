#include "FlowServerApp.h"

#include "critical/simulation/applications/server/FlowRequests_m.h"
#include "critical/flows/map/linear/LinearFlowMap.h"

#include <inet/common/lifecycle/ModuleOperations.h>
#include <inet/common/ModuleAccess.h>
#include <inet/networklayer/common/L3AddressResolver.h>
#include <inet/networklayer/common/L3AddressTag_m.h>
#include <inet/transportlayer/common/L4PortTag_m.h>

namespace critical {

Define_Module(FlowServerApp);  
  
FlowServerApp::FlowServerApp() {
  flowMap = new LinearFlowMap<RequestInfo>();
}

FlowServerApp::~FlowServerApp() {
  cancelAndDelete(timer);
  delete flowMap;
}

void FlowServerApp::initialize(int stage) {
  ApplicationBase::initialize(stage);
  if (stage == inet::INITSTAGE_LOCAL) {
    timer = new cMessage("timer");

    // Initialize parameters
    port = par("port").intValue();
    startTime = par("startTime");
    protocol = inet::getModuleFromPar<CriticalProtocol>(par("criticalProtocol"), this);
    if (!protocol) {
      throw cRuntimeError("This application should run in a router with a critical protocol");
    }
    protocol->addListener(this);

    // stats
    numAccepted = 0;
    numFailed = 0;
    numReceived = 0;
    numReroutesAccepted = 0;
    numReroutesFailed = 0;
  }
}

void FlowServerApp::handleMessageWhenUp(cMessage* msg) {
  if (msg == timer) {
    socket.setOutputGate(gate("socketOut"));
    socket.bind(port);
    socket.setCallback(this);
  }
  else {
    socket.processMessage(msg);
  }
}

void FlowServerApp::processPacket(inet::Packet* packet) {
  const FlowRequestPacketBase* baseRequest = packet->peekAtFront<FlowRequestPacketBase>().get();
  FlowId flow(baseRequest->getSource(), baseRequest->getDestination(), baseRequest->getLabel());
 
  switch (baseRequest->getType()) {
    case FLOW_REQUEST: {
      const FlowRequestPacket* request = packet->peekAtFront<FlowRequestPacket>().get();
      numReceived++;  

      RequestInfo info;
      info.accepted = false;
      info.srcAddress = packet->findTag<inet::L3AddressInd>()->getSrcAddress();
      info.port = packet->findTag<inet::L4PortInd>()->getSrcPort();
      flowMap->insertFlow(flow, info);

      // Initiate the routing process
      protocol->initiateRouting(
        flow.src,
        flow.dest,
        flow.label,
        request->getDelay() * 1000, 
        request->getBandwidth(),
        request->getBurst() * 8
      );
    } break;

    case FLOW_FREE: {
      flowMap->deleteFlow(flow);
      protocol->free(flow.src, flow.dest, flow.label);
    } break;
      
    default: {
      EV_WARN << "Received invalid packet\n";
    } break;
  }
  delete packet;
}

void FlowServerApp::refreshDisplay() const {
    ApplicationBase::refreshDisplay();
    char buf[100];
    sprintf(buf, "rcvd: %d\naccepts: %d\nfailed: %d", numReceived, numAccepted, numFailed);
    getDisplayString().setTagArg("t", 0, buf);
}

void FlowServerApp::finish() {
  recordScalar("flowRequestsReceived", numReceived);
  recordScalar("flowRequestsAccepted", numAccepted);
  recordScalar("flowRequestsFailed", numFailed);
  recordScalar("flowRequestsOngoing", numReceived - (numAccepted + numFailed));
  recordScalar("flowReroutesAccepted", numReroutesAccepted);
  recordScalar("flowReroutesFailed", numReroutesFailed);
  recordScalar("flowReroutesReceived", numReroutesAccepted + numReroutesFailed);
}

void FlowServerApp::handleStartOperation(inet::LifecycleOperation* operation) {
  if (startTime < simTime()) {
    scheduleAt(simTime(), timer);
  }
  else {
    scheduleAt(startTime, timer);
  }
}

void FlowServerApp::handleStopOperation(inet::LifecycleOperation* operation) {
  cancelEvent(timer);
  socket.close();
}

void FlowServerApp::handleCrashOperation(inet::LifecycleOperation* operation) {
  cancelEvent(timer);
  socket.destroy();
}

void FlowServerApp::onRoutingComplete(
  const inet::Ipv6Address& source, 
  const inet::Ipv6Address& dest, 
  uint32_t label, 
  bool accepted
) {
  Enter_Method("onRoutingComplete()");

  FlowId flow(source, dest, label);

  FlowMapEntry<RequestInfo>* entry = flowMap->lookupFlow(flow);
  if (!entry) {
    return;
  }

  inet::Packet* response = new inet::Packet("Flow request-response");

  if (entry->data.accepted) {
    // Reroute
    auto data = inet::makeShared<FlowInterruptedPacket>();
    data->setSource(flow.src);
    data->setDestination(flow.dest);
    data->setLabel(flow.label);
    data->setContinued(accepted);
    response->insertAtFront(data);
    if (accepted) 
      numReroutesAccepted++;
    else
      numReroutesFailed++;
  }
  else { 
    // Normal routing 
    auto data = inet::makeShared<FlowResponsePacket>();
    data->setSource(flow.src);
    data->setDestination(flow.dest);
    data->setLabel(flow.label);
    data->setAccepted(accepted);
    response->insertAtFront(data);
    entry->data.accepted = accepted;
    if (accepted) 
      numAccepted++;
    else
      numFailed++;
  }

  socket.sendTo(response, entry->data.srcAddress, entry->data.port);

  if (!accepted) {
    flowMap->deleteFlow(flow);
  }
}

}