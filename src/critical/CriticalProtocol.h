#ifndef _CRITICAL_CRITICALPROTOCOL_H
#define _CRITICAL_CRITICALPROTOCOL_H

#include <omnetpp.h>
#include <inet/routing/base/RoutingProtocolBase.h>
#include <inet/networklayer/contract/IInterfaceTable.h>
#include <inet/networklayer/contract/IRoutingTable.h>
#include <inet/common/packet/Packet.h>
#include <inet/common/Protocol.h>
#include <inet/networklayer/contract/INetfilter.h>
#include <list>

#include "critical/common/routing/RouterBase.h"
#include "critical/flows/FlowTable.h"
#include "critical/common/util/Observable.h"
#include "critical/common/util/Parameterizable.h"
#include "critical/parameters/CriticalProtocolParameters.h"
#include "critical/queueing/dnc/PredictablePort.h"

using namespace omnetpp;

namespace critical {

class IRouteListener {
  public:
    virtual void onRoutingComplete(
      const inet::Ipv6Address& source, 
      const inet::Ipv6Address& dest, 
      uint32_t label, 
      bool accepted
    ) = 0;
};

class CriticalProtocol : 
  public inet::RoutingProtocolBase, 
  public inet::NetfilterBase::HookBase,
  public IFlowTableListener,
  public Observable<IRouteListener>,
  public IConsumptionListener,
  protected cListener {

  private: 
    cMessage* startUp = nullptr;
    cMessage* memoryTimer = nullptr;
    cModule* host = nullptr;
    std::map<cMessage*, inet::Packet*> delayQueue;

    RouterBase* router = nullptr;
    inet::IInterfaceTable* interfaceTable = nullptr;
    inet::IRoutingTable* routingTable = nullptr;
    inet::INetfilter* networkProtocol = nullptr;
    FlowTable flowTable;
    CriticalProtocolParameters params;
    
    uint32_t protocolPacketsSent;
    uint32_t criticalPacketsLost;
    uint32_t criticalDataLost;
    uint64_t protocolBytesSent;
    uint64_t maxMemoryFootprint;

    static simsignal_t consumptionSignal;
    static simsignal_t queueStateSignal;
    static simsignal_t routeSignal;
    static simsignal_t packetProcessingSignal;
    static simsignal_t flowSignalingSignal;
    static simsignal_t probeReservationSignal;

  public:
    uint32_t qosOverrides = 0;
    uint32_t collisions = 0;
    uint32_t straightFails = 0;
    uint32_t tries = 0;

    CriticalProtocol();
    virtual ~CriticalProtocol();

    inet::IInterfaceTable* getInterfaceTable() { return interfaceTable; };
    inet::InterfaceEntry* getLo() { return interfaceTable->findFirstLoopbackInterface(); };
    inet::IRoutingTable* getRoutingTable() { return routingTable; };
    RouterBase* getRouter() { return router; };
    FlowTable& getFlowTable() { return flowTable; };
    const CriticalProtocolParameters& getParams() { return params; };

    /**
     * @brief Initiates the routing process for the given flow. This starts the routing 
     * protocol to find an embedding for the flow.
     * 
     * @param source 
     * @param dest 
     * @param label 
     * @param delay 
     * @param bandwidth 
     * @param burst 
     */
    void initiateRouting(
      const inet::Ipv6Address& source, 
      const inet::Ipv6Address& dest, 
      uint32_t label, 
      uint64_t delay,
      uint64_t bandwidth,
      uint64_t burst
    );

    /**
     * @brief Signals that no path for the flow could be found. 
     * 
     * @param flow 
     */
    void signalRoutingFailed(const FlowId& flow);

    /**
     * @brief Frees the given flow
     * 
     * @param source 
     * @param dest 
     * @param label 
     */
    void free(
      const inet::Ipv6Address& source, 
      const inet::Ipv6Address& dest, 
      uint32_t label
    );

    /**
     * @brief Send a packet to the lower layers
     * 
     * @param packet 
     */
    void sendPacket(inet::Packet* packet);

    /**
     * @brief Send a packet to the lower layers
     * 
     * @param packet 
     */
    void sendPacketDelayed(inet::Packet* packet, double delay);

    /**
     * @brief Send a packet to the loopback interface
     * 
     * @param packet 
     */
    void sendPacketLo(inet::Packet* packet);

    // Define this as an INET protocol, 
    // such that we can register it as a service to the lower layer
    static const inet::Protocol asInetProtocol; 

    /**
     * @brief If a flow is confirmed in the flow table, we can signal it to our listeners that 
     * the routing of the flow is confirmed.
     * 
     * @param entry 
     */
    virtual void onFlowAccepted(const FlowTableEntry* entry) override;

    /**
     * @brief If a flow is deleted from the flow table, we can signal to our listeners that 
     * the routing of the flow is completed, but that the flow was not accepted.
     * 
     * @param entry 
     */
    virtual void onFlowDelete(const FlowTableEntry* entry) override;

    virtual void onConsumptionChange(int id, bool significant, bool up) override;

    /**
     * Callback to be called when a confirmed path is being signaled into the network 
     **/
    void onPathSignaling(const FlowId& flowId);

    /**
     * Callback to be called when a probe greedily reserves resources 
     **/
    void onProbeReservation(const FlowId& flowId, int reservationsDelta);

  protected:
    virtual void initialize(int stage) override;
    
    using cListener::finish;
    virtual void finish() override;
    virtual void handleMessageWhenUp(cMessage* msg) override;

    // cListener

    virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details) override;

    // Netfilter

    virtual Result datagramPreRoutingHook(inet::Packet* datagram) override;
    virtual Result datagramForwardHook(inet::Packet* datagram) override { return ACCEPT; }
    virtual Result datagramPostRoutingHook(inet::Packet* datagram) override { return ACCEPT; }
    virtual Result datagramLocalInHook(inet::Packet* datagram) override { return ACCEPT; }
    virtual Result datagramLocalOutHook(inet::Packet* datagram) override { return ACCEPT; };

    // Lifecycle 

    virtual void handleStartOperation(inet::LifecycleOperation* operation) override;
    virtual void handleStopOperation(inet::LifecycleOperation* operation) override;
    virtual void handleCrashOperation(inet::LifecycleOperation* operation) override;

  private:
    void recordMemoryFootprint();

  private:
    RouterBase* createRouter();

    void subscribeSignals();
    void unsubscribeSignals();
};

}

#endif 