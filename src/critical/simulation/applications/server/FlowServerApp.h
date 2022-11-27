#ifndef __FlowServerApp_H__
#define __FlowServerApp_H__

#include "critical/CriticalProtocol.h"
#include "critical/flows/map/IFlowMap.h"

#include <inet/applications/base/ApplicationBase.h>
#include <inet/transportlayer/contract/udp/UdpSocket.h>

using namespace omnetpp;

namespace critical {

class FlowServerApp : 
  public inet::ApplicationBase, 
  public inet::UdpSocket::ICallback,
  public IRouteListener {

  private:
    int port;

    CriticalProtocol* protocol;
    inet::UdpSocket socket;
    cMessage* timer;
    simtime_t startTime;

    int numAccepted;
    int numFailed;
    int numReceived;
    int numReroutesAccepted;
    int numReroutesFailed;

    // The running requests
    struct RequestInfo {
      inet::L3Address srcAddress;
      int port;
      bool accepted = false;
    };
    IFlowMap<RequestInfo>* flowMap;

  public:
    FlowServerApp();
    virtual ~FlowServerApp();
  
  protected:
    virtual int numInitStages() const override { return inet::NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessageWhenUp(cMessage *msg) override;
    virtual void refreshDisplay() const override;
    virtual void finish() override;

    virtual void processPacket(inet::Packet* msg);

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

    /**
     * @brief Listen to flow accept and denies of the underlying protocol
     * 
     * @param source 
     * @param dest 
     * @param label 
     * @param accepted 
     */
    virtual void onRoutingComplete(
      const inet::Ipv6Address& source, 
      const inet::Ipv6Address& dest, 
      uint32_t label, 
      bool accepted
    ) override;

};

}


#endif // __FlowServerApp_H__