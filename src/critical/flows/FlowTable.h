#ifndef _CRITICAL_FLOWTABLE_H
#define _CRITICAL_FLOWTABLE_H

#include <inet/networklayer/common/InterfaceEntry.h>
#include <vector>

#include "Flow.h"
#include "critical/common/util/Observable.h"
#include "critical/flows/map/IFlowMap.h"
#include "critical/common/util/NonCopyable.h"


namespace critical {

struct FlowTableData {
  FlowParameters params;
  int nextInterface;
  int prevInterface;
  inet::Ipv6Address nextHop;
  int queueNumber;
  bool firstHop = false;
  bool finalHop = false;
  bool confirmed = false;

  FlowTableData(
    FlowParameters params,
    int nextInterface,
    int prevInterface,
    const inet::L3Address& nextHop,
    int queueNumber
  ) : 
    params(params), nextInterface(nextInterface), prevInterface(prevInterface), 
    nextHop(nextHop.toIpv6()), queueNumber(queueNumber) {};
};

/**
 * @brief An entry in the flowtable
 */
typedef FlowMapEntry<FlowTableData> FlowTableEntry;

/**
 * @brief A listener for the flow table
 */
class IFlowTableListener {
  public:
    virtual void onFlowAccepted(const FlowTableEntry* entry) = 0;
    virtual void onFlowDelete(const FlowTableEntry* entry) = 0;
};

/**
 * @brief The flow table itself
 */
class FlowTable: public Observable<IFlowTableListener>, public NonCopyable {
  private:
    IFlowMap<FlowTableData>* flowMap;

  public:
    FlowTable();
    virtual ~FlowTable();

    FlowTableEntry& embedFlow(
      const FlowId id,
      const FlowParameters params,
      int interface, 
      const inet::L3Address& nextHop,
      int prevInterface,
      int queueNumber,
      bool isFinalHop = false,
      bool isFirstHop = false,
      bool confirmed = true
    );

    /**
     * @brief Performs a lookup of the given flow parameters in the flow table. 
     * Returns a null pointer if no such flow is found.
     * 
     * @param src The source address
     * @param dest The destination address
     * @param label The flow label
     * @return const Flow* A pointer to the flow 
     */
    FlowTableEntry* lookup(
      const inet::L3Address& src, 
      const inet::L3Address& dest, 
      uint32_t label
    );

    /**
     * @brief 
     * 
     * @param flow 
     * @return true 
     * @return false 
     */
    bool contains(const FlowId& flow) { return lookup(flow.src, flow.dest, flow.label) != nullptr; };

    /**
     * @brief 
     * 
     * @param flow 
     */
    FlowTableEntry* confirm(const FlowId& flow);

    /**
     * @brief Delete a flow from the flowtable
     * 
     * @param src The source address 
     * @param dest The destination address
     * @param label The flow label
     */
    FlowTableEntry deleteFlow(
      const inet::L3Address& src, 
      const inet::L3Address& dest, 
      uint32_t label
    );

  private:
    void onDelete(const FlowTableEntry* entry);
    void onConfirm(const FlowTableEntry* entry);
};

}


#endif 