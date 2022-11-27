#ifndef _CRITICAL_IFLOWMAP_H
#define _CRITICAL_IFLOWMAP_H

#include <inet/networklayer/common/L3Address.h>
#include <optional>

#include "critical/flows/Flow.h"

namespace critical {

template <class T>
struct FlowMapEntry {
  FlowId flow;
  T data;

  FlowMapEntry(const FlowId& id, T data) : flow(id), data(data) {};
  FlowMapEntry(const FlowMapEntry<T>& other): flow(other.flow), data(other.data) {};
};

template <class T>
class IFlowMap {
  public:
    virtual ~IFlowMap() { clear(); };

    /**
     * @brief Clears all entries in the table.
     * 
     */
    virtual void clear() {};

    /**
     * @brief Dynamically allocates a new entry and inserts it into the table.
     * 
     * @param flow 
     * @param data 
     * @return FlowMapEntry<T>* 
     */
    virtual FlowMapEntry<T>* insertFlow(const FlowId& flow, T data) = 0;

    /**
     * @brief Removes the entry from the map and deletes the memory. A copy of the entry 
     * is returned.
     * 
     * @param flow 
     * @return FlowMapEntry<T> 
     */
    virtual FlowMapEntry<T> deleteFlow(const FlowId& flow) = 0;

    /**
     * @brief Removes the entry from the map and deletes the memory, if possible. 
     * An optional copy of the entry is returned.
     * 
     * @param flow 
     * @return std::optional<FlowMapEntry<T>> 
     */
    virtual std::optional<FlowMapEntry<T>> deleteFlowIfPresent(const FlowId& flow) = 0;

    /**
     * @brief Looks up the entry in the map and returns it. 
     * 
     * @param flow 
     * @return FlowMapEntry<T>* 
     */
    virtual FlowMapEntry<T>* lookupFlow(const FlowId& flow) = 0;

    /**
     * @brief Removes the entry from the map but the memory is NOT deleted. 
     * A pointer to the dynamically allocated entry is returned. The user should delete 
     * this pointer himself.
     * 
     * @param flow 
     * @return FlowMapEntry<T>* 
     */
    virtual FlowMapEntry<T>* removeFlow(const FlowId& flow) = 0;

    /**
     * @brief Checks if an entry for the given flow exists in the map.
     * 
     * @param flow 
     * @return true 
     * @return false 
     */
    virtual bool contains(const FlowId& flow) {
      return lookupFlow(flow) != nullptr;
    };

};

}

#endif 