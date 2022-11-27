#include "CriticalUdpApp.h"

#include "critical/simulation/recorder/FlowRecorderData.h"

#include <inet/networklayer/common/L3AddressResolver.h>
#include <inet/applications/base/ApplicationPacket_m.h>
#include <inet/common/TimeTag_m.h>
#include <inet/networklayer/ipv6/Ipv6RoutingTable.h>
#include <inet/networklayer/common/FlowLabelTag_m.h>

namespace critical {

Define_Module(CriticalUdpApp);

simsignal_t CriticalUdpApp::flowRequestSignal = registerSignal("flowRequestSignal");
simsignal_t CriticalUdpApp::flowResponseSignal = registerSignal("flowResponseSignal");
simsignal_t CriticalUdpApp::flowRerouteSignal = registerSignal("flowRerouteSignal");

CriticalUdpApp::CriticalUdpApp() {
  
}

CriticalUdpApp::~CriticalUdpApp() {
  cancelAndDelete(timer);
}

void CriticalUdpApp::initialize(int stage) {
  ApplicationBase::initialize(stage);
  if (stage == inet::INITSTAGE_LOCAL) {
    timer = new cMessage("timer");
    startTime = par("startTime");
    maxPacketsToSend = par("maxPacketsToSend");
    requestSent = false;
    srcPort = par("port").intValue();
    destPort = par("destPort").intValue();
    delay = par("delay").intValue();
    bandwidth = par("bandwidth").intValue();
    burst = par("burst").intValue();
    packetBurst = par("packetBurst").intValue();
    totalBurst = burst * packetBurst;
    noTraffic = par("noTraffic").boolValue();
    noTrafficStop = par("noTrafficStop");
    duration = par("duration");
    
    label = (uint32_t)par("label").intValue() & (uint32_t)0xFFFFF;
    if (par("label").intValue() <= 0) {
      throw cRuntimeError("Flow label should be greater than 0");
    }

    numSent = 0;
    packetDataLength = burst - 18 - 40 - 8; // ETH + IP + UDP

    interval = (8 * (double)totalBurst) / (double)bandwidth; 
  }
}

void CriticalUdpApp::handleMessageWhenUp(cMessage* msg) {
  if (msg == timer) {
    switch (msg->getKind()) {
      case MsgKinds::START: {
        resolveAddresses();
        EV_INFO << "Booted up critical UDP application\n";
        EV_INFO << "  - " << srcAddress.toIpv6() <<  " -> " << destAddress.toIpv6() << "\n";
        EV_INFO << "  - server:    " << flowServerAddress << "\n";
        EV_INFO << "  - delay:     " << delay << "ms\n";
        EV_INFO << "  - bandwidth: " << bandwidth << "bps\n";
        EV_INFO << "  - burst:     " << burst << "B\n";
        EV_INFO << "  - label:     " << label << "\n";

        socket.setOutputGate(gate("socketOut"));
        socket.bind(srcPort);
        socket.setCallback(this);
        sendRequest();
      } break;
      case MsgKinds::SEND: {
        if (shouldSend()) {
          for (int i = 0; i < packetBurst; i++) {
            sendPacket();
          }
          scheduleAt(simTime() + interval, timer);
        }
        else {
          sendFree();
        }
      } break;
      case MsgKinds::FREE: {
        sendFree();
      } break;
      default: {
        throw cRuntimeError("Invalid message kind");
      } break;
    }
  }
  else {
    socket.processMessage(msg);
  }
}

void CriticalUdpApp::sendRequest() {
  auto data = inet::makeShared<FlowRequestPacket>();
  data->setSource(srcAddress.toIpv6());
  data->setDestination(destAddress.toIpv6());
  data->setLabel(label);
  data->setDelay(delay);
  data->setBandwidth(bandwidth);
  data->setBurst(totalBurst);

  inet::Packet* packet = new inet::Packet("Flow request");
  packet->insertAtBack(data);

  socket.sendTo(packet, flowServerAddress, 4096);
  requestSent = true;

  FlowRequestData signalData(this);
  emit(flowRequestSignal, &signalData);
}

void CriticalUdpApp::sendPacket() {
  const auto& payload = inet::makeShared<inet::ApplicationPacket>();
  payload->setChunkLength(inet::B(packetDataLength));
  payload->setSequenceNumber(numSent);
  payload->addTag<inet::CreationTimeTag>()->setCreationTime(simTime());

  
  inet::Packet* packet = new inet::Packet("data");
  packet->insertAtBack(payload);
  packet->addTag<inet::FlowLabelReq>()->setFlowLabel(label);

  socket.sendTo(packet, destAddress, destPort);
  numSent++;
}

void CriticalUdpApp::processPacket(inet::Packet* packet) {
  const auto& base = packet->peekAtFront<FlowRequestPacketBase>();
  switch (base->getType()) {
    case FLOW_RESPONSE: {
      handleResponse(packet->peekAtFront<FlowResponsePacket>().get());
    } break;
    case FLOW_INTERRUPTED: {
      handleInterrupted(packet->peekAtFront<FlowInterruptedPacket>().get());
    } break;
    default: {
      EV_WARN << "Received unexpected packet\n";
    } break;
  }
  delete packet;
}

void CriticalUdpApp::handleResponse(const FlowResponsePacket* response) {
  if (!requestSent) {
    throw cRuntimeError("Got response while not sending out request");
  }
  if (response->getAccepted()) {
    // Start sending packets
    if (!noTraffic) {
      timer->setKind(MsgKinds::SEND);
      scheduleAt(simTime() + interval, timer);
    }
    else {
      if (!noTrafficStop.isZero()) {
        if (!duration.isZero()) {
          if (simTime() + duration <= noTrafficStop) {
            timer->setKind(MsgKinds::FREE);
            scheduleAt(simTime() + duration, timer);
          }
          else {
            timer->setKind(MsgKinds::SEND);
            if (noTrafficStop > simTime())
              scheduleAt(noTrafficStop, timer);
            else 
              scheduleAt(simTime(), timer);
          }
        }
        else {
          timer->setKind(MsgKinds::SEND);
          if (noTrafficStop > simTime())
            scheduleAt(noTrafficStop, timer);
          else 
            scheduleAt(simTime(), timer);
        }
      }
      else if (!duration.isZero()) {
        timer->setKind(MsgKinds::FREE);
        scheduleAt(simTime() + duration, timer);
      }
    }
  }

  FlowResponseData data(this, response->getAccepted());
  emit(flowResponseSignal, &data);
}

void CriticalUdpApp::handleInterrupted(const FlowInterruptedPacket* interrupt) {
  if (!interrupt->getContinued()) {
    cancelEvent(timer);
  }

  FlowRerouteData data(this, interrupt->getContinued());
  emit(flowRerouteSignal, &data);
}

void CriticalUdpApp::sendFree() {
  auto data = inet::makeShared<FlowFreePacket>();
  data->setSource(srcAddress.toIpv6());
  data->setDestination(destAddress.toIpv6());
  data->setLabel(label);

  inet::Packet* packet = new inet::Packet("Flow free request");
  packet->insertAtBack(data);
  
  socket.sendTo(packet, flowServerAddress, 4096);
}

void CriticalUdpApp::finish() {
  recordScalar("packets sent", numSent);
}

void CriticalUdpApp::refreshDisplay() const {
  ApplicationBase::refreshDisplay();

  char buf[100];
  sprintf(buf, "sent: %d", numSent);
  getDisplayString().setTagArg("t", 0, buf);
}

void CriticalUdpApp::handleStartOperation(inet::LifecycleOperation* operation) {
  timer->setKind(MsgKinds::START);
  if (startTime < simTime()) {
    startTime = simTime();
  }
 
  scheduleAt(startTime, timer);
}

void CriticalUdpApp::handleStopOperation(inet::LifecycleOperation* operation) {
  cancelEvent(timer);
  socket.close();
}

void CriticalUdpApp::handleCrashOperation(inet::LifecycleOperation* operation) {
  cancelEvent(timer);
  socket.destroy();
}

void CriticalUdpApp::resolveAddresses() {
    inet::L3AddressResolver().tryResolve(par("srcAddress"), srcAddress);
    if (srcAddress.isUnspecified() || srcAddress.isLinkLocal()) {
      throw cRuntimeError("Unresolved source address");
    }
    inet::L3AddressResolver().tryResolve(par("destAddress"), destAddress);
    if (destAddress.isUnspecified() || destAddress.isLinkLocal()) {
      throw cRuntimeError("Unresolved destination address");
    }
    inet::L3AddressResolver().tryResolve(par("flowServerAddress"), flowServerAddress);
    if (flowServerAddress.isUnspecified() || flowServerAddress.isLinkLocal()) {
      throw cRuntimeError("Unresolved flow server address");
    }
}

bool CriticalUdpApp::shouldSend() {
  return (maxPacketsToSend < 0 || numSent < maxPacketsToSend) && 
  (duration.isZero() || simTime() <= startTime + duration);
}

}