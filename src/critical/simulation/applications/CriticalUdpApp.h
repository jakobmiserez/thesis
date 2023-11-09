#ifndef __CRITICALUDPAPP_H
#define __CRITICALUDPAPP_H

#include "critical/simulation/applications/server/FlowRequests_m.h"
#include "critical/flows/Flow.h"

#include <inet/applications/base/ApplicationBase.h>
#include <inet/transportlayer/contract/udp/UdpSocket.h>

using namespace omnetpp;

namespace critical {

class CriticalUdpApp:
  public inet::ApplicationBase, 
  public inet::UdpSocket::ICallback {
  
  private:
    enum MsgKinds { START = 1, SEND, FREE };
    
    cMessage* timer = nullptr;
    simtime_t startTime;
    simtime_t duration;
    simtime_t interval;
    int maxPacketsToSend;
    int srcPort;
    int destPort;
    uint64_t delay;
    uint64_t bandwidth;
    uint64_t burst;
    int packetBurst;
    uint64_t totalBurst;
    int packetDataLength;
    int numSent;
    uint32_t label;
    bool requestSent;
    bool noTraffic;
    simtime_t noTrafficStop;
    inet::UdpSocket socket;
    inet::L3Address destAddress;
    inet::L3Address srcAddress;
    inet::L3Address flowServerAddress;

    static simsignal_t flowRequestSignal;
    static simsignal_t flowResponseSignal;
    static simsignal_t flowRerouteSignal;

  public:
    CriticalUdpApp();
    virtual ~CriticalUdpApp();

  protected:
    virtual int numInitStages() const override { return inet::NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessageWhenUp(cMessage *msg) override;
    virtual void refreshDisplay() const override;
    virtual void finish() override;

    virtual void handleStartOperation(inet::LifecycleOperation *operation) override;
    virtual void handleStopOperation(inet::LifecycleOperation *operation) override;
    virtual void handleCrashOperation(inet::LifecycleOperation *operation) override;

    virtual void socketDataArrived(inet::UdpSocket* socket, inet::Packet* packet) override {
      processPacket(packet);
    };

    virtual void socketErrorArrived(inet::UdpSocket *socket, inet::Indication *indication) override {
      EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
      delete indication;
    };

    virtual void socketClosed(inet::UdpSocket *socket) override {};

  private:
    void sendRequest();
    void sendPacket();
    void sendFree();
    void handleResponse(const FlowResponsePacket* response);
    void handleInterrupted(const FlowInterruptedPacket* interrupt);

    void processPacket(inet::Packet* msg);
    void resolveAddresses();
    bool shouldSend();

    FlowId getFlowId() const;

};

}

#endif 