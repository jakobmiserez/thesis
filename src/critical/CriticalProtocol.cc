#include "CriticalProtocol.h"

#include <omnetpp.h>
#include <inet/common/ProtocolGroup.h>
#include <inet/common/IProtocolRegistrationListener.h>
#include <inet/common/ModuleAccess.h>
#include <inet/networklayer/ipv6/Ipv6Header_m.h>
#include <inet/networklayer/common/NextHopAddressTag_m.h>
#include <inet/linklayer/common/InterfaceTag_m.h>
#include <chrono>

#include "critical/protocols/probing/ProbingRouter.h"
#include "critical/protocols/ls/LsRouter.h"
#include "critical/queueing/classifier/QosQueueReq_m.h"
#include "critical/parameters/ParameterReader.h"
#include "simulation/recorder/ConsumptionRecorder.h"
#include "simulation/recorder/QueueRecorder.h"
#include "simulation/recorder/FlowRecorderData.h"

using namespace omnetpp;

namespace critical {

// Register this as an Omnet++ module
Define_Module(CriticalProtocol);

// Initialize static variables
const inet::Protocol CriticalProtocol::asInetProtocol("critical", "CRITICAL");
simsignal_t CriticalProtocol::consumptionSignal = registerSignal("consumptionSignal");
simsignal_t CriticalProtocol::queueStateSignal = registerSignal("queueStateSignal");

simsignal_t CriticalProtocol::routingSignal = registerSignal("routingSignal");
simsignal_t CriticalProtocol::routingSuccessSignal = registerSignal("routingSuccessSignal");
simsignal_t CriticalProtocol::routingFailSignal = registerSignal("routingFailSignal");
simsignal_t CriticalProtocol::baseRoutingSignal = registerSignal("baseRoutingSignal");
simsignal_t CriticalProtocol::baseRoutingSuccessSignal = registerSignal("baseRoutingSuccessSignal");
simsignal_t CriticalProtocol::baseRoutingFailSignal = registerSignal("baseRoutingFailSignal");

simsignal_t CriticalProtocol::packetProcessingSignal = registerSignal("packetProcessingSignal");
simsignal_t CriticalProtocol::flowSignalingSignal = registerSignal("flowSignalingSignal");
simsignal_t CriticalProtocol::probeReservationSignal = registerSignal("probeReservationSignal");


CriticalProtocol::CriticalProtocol() {
  inet::ProtocolGroup::ipprotocol.addProtocol(asInetProtocol.getId(), &asInetProtocol);
  flowTable.addListener(this);
}

CriticalProtocol::~CriticalProtocol() {
  flowTable.removeListener(this);
  cancelAndDelete(startUp);
  cancelAndDelete(memoryTimer);
  for (auto [timer, packet]: delayQueue) {
    delete packet;
    cancelAndDelete(timer);
  }
  delete router;
}

void CriticalProtocol::initialize(int stage) {
  RoutingProtocolBase::initialize(stage);
  if (stage == inet::INITSTAGE_LOCAL) {
    // Initialize local information
    startUp = new cMessage("Critical protocol start-up");
    memoryTimer = new cMessage("Critical protocol memory optimizer");
    interfaceTable = inet::getModuleFromPar<inet::IInterfaceTable>(par("interfaceTableModule"), this);
    routingTable = inet::getModuleFromPar<inet::IRoutingTable>(par("routingTableModule"), this);
    networkProtocol = inet::getModuleFromPar<inet::INetfilter>(par("networkProtocolModule"), this);
    host = inet::getContainingNode(this);
    
    params = ParameterReader().readParams(this);
    criticalPacketsLost = 0;
    protocolPacketsSent = 0;
    protocolBytesSent = 0;
    maxMemoryFootprint = 0;
  }
  else if (stage == inet::INITSTAGE_ROUTING_PROTOCOLS) {
    inet::registerService(asInetProtocol, nullptr, gate("ipIn"));
    inet::registerProtocol(asInetProtocol, gate("ipOut"), nullptr);
    networkProtocol->registerHook(0, this);
  }
}

void CriticalProtocol::finish() {
  recordScalar("packetsLost", criticalPacketsLost);
  recordScalar("dataLost", criticalDataLost);
  recordScalar("protocolPacketsSent", protocolPacketsSent);
  recordScalar("protocolBytesSent", protocolBytesSent);
  recordScalar("qosOverrides", qosOverrides);
  recordScalar("collisions", collisions);
  recordScalar("straightFails", straightFails);
  recordScalar("inaccuracyFails", inaccuracyFails);
  recordScalar("maxMemoryFootprint", maxMemoryFootprint);
  recordScalar("tries", tries);
  recordScalar("eventBasedUpdates", eventBasedUpdates);

  for (int i = 1; i < router->numPorts(); i++) {
    const auto& port = router->getPort(i);
    std::string baseName = "consumption";
    baseName += std::to_string(i);
    recordScalar(baseName.c_str(), port.getConsumptionChecker().getAbsoluteConsumption());
  }

}

void CriticalProtocol::handleMessageWhenUp(cMessage* msg) {
  if (msg == startUp) {
    // Boot up the protocol  
    EV_INFO << "(CRITICAL PROTOCOL) Booting up critical protocol (" << params.routingProtocol << ")\n";
    router = createRouter();
    router->start(0);
    for (int i = 0; i < router->numPorts(); i++) {
      auto& port = router->getPort(i);
      port.addListener(this);

      if (params.recordQueueStates) {
        for (int q = 0; q < port.getNumQueues(); q++) {
          const auto& queue = router->getPort(i).getQueues()[q];
          QueueRecorderData queueData(this, port.getId(), q, 
          queue.getQueueingDelayBound(), queue.getDelayBudgetInSeconds(),
          queue.getBufferSizeBound(), queue.getBufferSizeBudget());
          emit(queueStateSignal, &queueData);
        }
      }
    }
    subscribeSignals();
  }
  else if (msg == memoryTimer) {
    recordMemoryFootprint();
  }
  else {
    auto it = delayQueue.find(msg);
    if (it == delayQueue.end()) {

      auto startTime = std::chrono::high_resolution_clock::now();

      // Pass the message to the router message handler
      router->getMessageHandler()->receiveMessage(msg);

      auto endTime = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
      emit(packetProcessingSignal, (long)duration.count());

      if (params.recordMemoryFootprint && !params.optimizeMemoryFootprintRecording) {
        // Record memory footprint after message was handled
        recordMemoryFootprint();
      }
    }
    else {
      sendPacket((*it).second);
      delete (*it).first;
      delayQueue.erase(msg);
    }
  }
}

void CriticalProtocol::handleStartOperation(inet::LifecycleOperation* operation) {
  // Schedule the startup timer message to boot up the protocol
  SimTime next(2, SimTimeUnit::SIMTIME_S);
  scheduleAt(simTime() + next, startUp);

  if (params.optimizeMemoryFootprintRecording) {
    scheduleAt(SimTime(19, SimTimeUnit::SIMTIME_S), memoryTimer);
  }
}

void CriticalProtocol::handleStopOperation(inet::LifecycleOperation* operation) {
  unsubscribeSignals();
}

void CriticalProtocol::handleCrashOperation(inet::LifecycleOperation* operation) {
  unsubscribeSignals();
}

void CriticalProtocol::sendPacket(inet::Packet* packet) {
  Enter_Method("sendPacket()");
  take(packet);

  int queue = getParams().protocolQueue;
  if (queue >= 0) {
    packet->addTag<QosQueueReq>()->setQueue(queue);
  }

  send(packet, gate("ipOut"));
  if (simTime() > params.countPacketStatsAfter) {
    protocolBytesSent += packet->getByteLength();
    protocolPacketsSent++;
  }
}

void CriticalProtocol::sendPacketDelayed(inet::Packet* packet, double delay) {
  cMessage* msg = new cMessage("delayed sending");
  delayQueue[msg] = packet;
  scheduleAt(simTime() + delay, msg);
}

void CriticalProtocol::sendPacketLo(inet::Packet* packet) {
  int lo = getLo()->getInterfaceId();
  packet->addTagIfAbsent<inet::InterfaceInd>()->setInterfaceId(lo);
  router->getMessageHandler()->receiveMessage(packet);
}

void CriticalProtocol::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details) {
  if (signalID == inet::interfaceCreatedSignal) {
    EV_INFO << "(CRITICAL PROTOCOL) Interface created\n";
  }
  else if (signalID == inet::interfaceDeletedSignal) {
    EV_INFO << "(CRITICAL PROTOCOL) Interface deleted\n";
  }
  else if (signalID == inet::interfaceStateChangedSignal) {
    EV_INFO << "(CRITICAL PROTOCOL) Interface state changed\n";
    inet::InterfaceEntryChangeDetails* change = check_and_cast<inet::InterfaceEntryChangeDetails*>(obj);
    router->handleLinkFailure(change->getInterfaceEntry()->getInterfaceId());
  }
}

inet::INetfilter::IHook::Result CriticalProtocol::datagramPreRoutingHook(inet::Packet* datagram) {
  Enter_Method_Silent("datagramPreRoutingHook()");
  auto ipv6Header = datagram->peekAtFront<inet::Ipv6Header>();

  unsigned int flowLabel = ipv6Header->getFlowLabel();
  if (flowLabel > 0) {
    // The flow label is non-zero, so route it according to our flows
    EV_INFO << "(CRITICAL PROTOCOL) Got IPv6 packet with non-zero flowlabel\n";

    // Perform a lookup in the flow table
    inet::L3Address src = ipv6Header->getSourceAddress();
    inet::L3Address dest = ipv6Header->getDestinationAddress();
    EV_INFO << src << " --(" << flowLabel << ')' << '--> ' << dest << "\n";
    const FlowTableEntry* entry = flowTable.lookup(src, dest, flowLabel);

    if (entry != nullptr && entry->data.confirmed) {
      const auto& data = entry->data;
      // Found the flow entry, so route it according to the flow table

      EV_INFO << "(CRITICAL PROTOCOL) Accepted a flow packet. Setting the routing parameters.\n";
      inet::L3Address nextHop = data.nextHop.isUnspecified() ? dest : data.nextHop;
      datagram->addTagIfAbsent<inet::NextHopAddressReq>()->setNextHopAddress(nextHop);
      datagram->addTagIfAbsent<inet::InterfaceReq>()->setInterfaceId(data.nextInterface);
      datagram->addTagIfAbsent<QosQueueReq>()->setQueue(data.queueNumber);
      return ACCEPT;
    } 
    else {
      // Invalid packet label, it needs to be dropped

      EV_INFO << "(CRITICAL PROTOCOL) Dropped an invalid flow packet. \n";
      criticalPacketsLost++;
      criticalDataLost += datagram->getByteLength();
      return DROP;
    }
  } 
  // Flow label is zero, so best-effort traffic is allowed to be accepted

  EV_INFO << "(CRITICAL PROTOCOL) Accepted a best-effort packet \n";
  return ACCEPT;
}

///
// Private methods
///

RouterBase* CriticalProtocol::createRouter() {
  switch (params.routingProtocol) {
    case RoutingProtocol::LINK_STATE:
      return new ls::LsRouter(this);
    case RoutingProtocol::PROBING:
    default:
      return new probing::ProbingRouter(this);
  }
}

void CriticalProtocol::initiateRouting(
  const inet::Ipv6Address& source, 
  const inet::Ipv6Address& dest, 
  uint32_t label, 
  uint64_t delay,
  uint64_t bandwidth,
  uint64_t burst
) {
  Enter_Method_Silent("initiateRouting()");

  auto startTime = std::chrono::high_resolution_clock::now();
  
  // Initiate the routing process for this flow
  RouterBase::RouteResult res = router->startRouting(source, dest, label, delay, bandwidth, burst);

  auto endTime = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
  emit(routingSignal, (long)duration.count());
  if (res == RouterBase::RouteResult::ONGOING || res == RouterBase::RouteResult::ACCEPTED)
    emit(routingSuccessSignal, (long)duration.count());
  else if (res == RouterBase::RouteResult::FAILED)
    emit(routingFailSignal, (long)duration.count());

  if (params.recordBaselineRouting) {
    // Compare with a baseline routing algorithm
    startTime = std::chrono::high_resolution_clock::now();
    router->startBaseRouting(source, dest, label, delay, bandwidth, burst);
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    emit(baseRoutingSignal, (long)duration.count());

    if (res == RouterBase::RouteResult::ONGOING || res == RouterBase::RouteResult::ACCEPTED)
      emit(baseRoutingSuccessSignal, (long)duration.count());
    else if (res == RouterBase::RouteResult::FAILED)
      emit(baseRoutingFailSignal, (long)duration.count());
  }

  // If the flow is immediately  rejected, we can inform the listeners immediately
  if (res == RouterBase::RouteResult::FAILED) {
    signalRoutingFailed(FlowId(source, dest, label));
  }
}

void CriticalProtocol::signalRoutingFailed(const FlowId& flow) {
  notifyListeners([flow](IRouteListener* l){ l->onRoutingComplete(flow.src, flow.dest, flow.label, false); });
}

void CriticalProtocol::free(
  const inet::Ipv6Address& source, 
  const inet::Ipv6Address& dest, 
  uint32_t label
) {
  router->startFreeing(source, dest, label);
}

void CriticalProtocol::onFlowAccepted(const FlowTableEntry* entry) {
  if (entry->data.firstHop) {
    notifyListeners([entry](IRouteListener* l) {
      l->onRoutingComplete(
        entry->flow.src,
        entry->flow.dest, 
        entry->flow.label,
        true
      );
    });
  }

  if (params.recordConsumption) {
    // Emit consumption
    int id = entry->data.nextInterface;
    double maxc = (double)router->getPortById(id)->getLinkRate();
    double registered = entry->data.params.rate;
    ConsumptionRecorderData data(this, id, registered, maxc);
    emit(consumptionSignal, &data);
  }

  if (params.recordQueueStates) {
    // Emit queue
    int id = entry->data.nextInterface;
    const auto& queue = router->getPortById(id)->getQueues()[entry->data.queueNumber];
    QueueRecorderData queueData(this, id, entry->data.queueNumber, 
      queue.getQueueingDelayBound(), queue.getDelayBudgetInSeconds(),
      queue.getBufferSizeBound(), queue.getBufferSizeBudget()
    );
    emit(queueStateSignal, &queueData);
  }
}

void CriticalProtocol::onFlowDelete(const FlowTableEntry* entry) {

}

void CriticalProtocol::onConsumptionChange(int id, bool significant, bool up) {
  
}

void CriticalProtocol::subscribeSignals() {
  host->subscribe(inet::interfaceCreatedSignal, this);
  host->subscribe(inet::interfaceDeletedSignal, this);
  host->subscribe(inet::interfaceStateChangedSignal, this);
}

void CriticalProtocol::unsubscribeSignals() {
  host->unsubscribe(inet::interfaceCreatedSignal, this);
  host->unsubscribe(inet::interfaceDeletedSignal, this);
  host->unsubscribe(inet::interfaceStateChangedSignal, this);
}

void CriticalProtocol::recordMemoryFootprint() {
  uint64_t footprint = 0;
  footprint += flowTable.estimateMemoryFootprint();
  footprint += router->estimateMemoryFootprint();

  if (footprint > maxMemoryFootprint)
    maxMemoryFootprint = footprint;
}

void CriticalProtocol::onPathSignaling(const FlowId& flowId) {
  //FlowSignalingData data(flowId);
  //emit(flowSignalingSignal, &data);
}

void CriticalProtocol::onProbeReservation(const FlowId& flowId, int reservationsDelta) {
  ProbeReservationData data(flowId, reservationsDelta);
  emit(probeReservationSignal, &data);
}

}
