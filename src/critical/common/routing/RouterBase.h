#ifndef _CRITICAL_ROUTERBASE_H
#define _CRITICAL_ROUTERBASE_H

#include <omnetpp.h>
#include <inet/networklayer/contract/IRoutingTable.h>
#include <inet/networklayer/common/InterfaceEntry.h>

#include "critical/queueing/dnc/PredictablePort.h"
#include "critical/queueing/dnc/budget/ChameleonAllocator.h"
#include "critical/common/handler/top/TopLevelMessageHandler.h"
#include "critical/common/routing/Route.h"
#include "critical/common/util/FuncList.h"
#include "critical/common/util/Util.h"
#include "critical/common/util/Parameterizable.h"
#include "critical/common/failure/IFailureHandler.h"

#include <optional>

using namespace omnetpp;

namespace critical {

class CriticalProtocol;

class RouterBase: public Parameterizable, public IFailureHandler {
  public:
    enum RouteResult { ACCEPTED = 1, FAILED, ONGOING };
    struct LinkParameters {
      double delay; // delay in seconds
      double rate; // link rate in bps
    };

  protected:
    CriticalProtocol* protocol;
    cMessage* timer;

    inet::IRoutingTable* ipRoutingTable; // The real routing table that the ip module uses to route packets
    TopLevelMessageHandler* messageHandler;
    std::vector<inet::InterfaceEntry*> interfaces;

    std::vector<PredictablePort> ports;
    std::vector<int> portIds;
    std::map<int, PredictablePort*> idToPort;

  public:
    RouterBase(CriticalProtocol* protocol);
    virtual ~RouterBase();

    /**
     * @brief Starts the routing protocol with the certain delay. This method will fire a 
     * start timer message, and create the message handler.
     * 
     * @param delay 
     */
    virtual void start(double delay);

    TopLevelMessageHandler* getMessageHandler() { return messageHandler; };
    const std::vector<inet::InterfaceEntry*>& getInterfaces() const { return interfaces; };
    inet::InterfaceEntry* getInterfaceById(const int id) const;
    const cMessage* getStartTimer() { return timer; };
    const std::vector<PredictablePort>& getPorts() { return ports; };
    std::vector<int> getPortIds() { return portIds; };

    /**
     * @brief Get the ports of this router in a functional manner.
     * 
     * @param blacklist A set of port ids that will not be included
     * @return FuncList<PredictablePort*> 
     */
    FuncList<PredictablePort*> getPortsFunc(const std::set<int> blacklist = {}) { 
      return FuncList<int>::from(portIds)
        .filterMap<PredictablePort*>(
          [blacklist](int id) {
            return !contains(blacklist, id);
          }, 
          [this](int id) { 
            return getPortById(id); 
          }
        ); 
    }

    int numPorts() { return ports.size(); };
    PredictablePort& getPort(int i) { return ports[i]; };
    PredictablePort* getPortById(int id) { return idToPort.at(id); };

    /**
     * @brief Starts the routing process to find a route for the given flow.
     * 
     * @param source 
     * @param dest 
     * @param label 
     * @param delay 
     * @param bandwidth 
     * @param burst 
     * @return RouteResult If the routing process does not fail immediately
     */
    virtual RouteResult startRouting(
      const inet::Ipv6Address& source, 
      const inet::Ipv6Address& dest, 
      uint32_t label, 
      uint64_t delay,
      uint64_t bandwidth,
      uint64_t burst
    ) = 0;

    /**
     * @brief Starts the process to free the flow
     * 
     * @param source 
     * @param dest 
     * @param label 
     */
    virtual void startFreeing(
      const inet::Ipv6Address& source, 
      const inet::Ipv6Address& dest, 
      uint32_t label
    ) = 0;

    /**
     * @brief Safely downcast this router object
     * 
     * @tparam T Type of the downcast type
     * @return T* Pointer to this router
     */
    template <class T>
    T* as() {
      return check_and_cast<T*>(this);
    };

    /**
     * @brief Checks if this router is the final destination for the given address.
     * 
     * @param address 
     * @return true 
     * @return false 
     */
    bool isDestinationRouterFor(const inet::Ipv6Address& address);

    /**
     * @brief Checks if the given address is a local address or not 
     * 
     * @param address 
     * @return true 
     * @return false 
     */
    bool isLocalAddress(const inet::Ipv6Address& address);

    /**
     * @brief Gets the route for the given destination, if it exists, by looking at the 
     * standard IP routing table
     * 
     * @param address 
     * @return std::optional<Route> 
     */
    std::optional<Route> getRouteFor(const inet::Ipv6Address& address);

    /**
     * @brief Prints the standard IP routing table
     */
    void printRoutingTable() {
      ipRoutingTable->printRoutingTable();
    };

    /**
     * @brief Reroutes the given flow
     * 
     * @param flow 
     * @param params 
     */
    void reroute(const FlowId& flow, const FlowParameters& params);
    void reroute(const Flow& flow) { reroute(flow.id, flow.params); };
  
  protected:
    /**
     * @brief Create the message handler for this router.
     * 
     * @return MessageHandlerBase* 
     */
    virtual TopLevelMessageHandler* createMessageHandler() = 0;

    /**
     * @brief Get the Link Parameters for the given interface. This gets the delay and bandwidth parameters
     * 
     * @param entry 
     * @return LinkParameters 
     */
    LinkParameters getLinkParameters(inet::InterfaceEntry* entry);

  private:
    void initializeInterfaces();
};

}

#endif