#ifndef _CRITICAL_LS_PATHTABLE_H
#define _CRITICAL_LS_PATHTABLE_H

#include "critical/common/util/Parameterizable.h"
#include "critical/flows/Flow.h"
#include "critical/flows/map/linear/LinearFlowMap.h"
#include "critical/common/util/Util.h"
#include "critical/common/util/NonCopyable.h"
#include "critical/protocols/ls/util/LsDefs.h"
#include "critical/protocols/ls/topology/Topology.h"

#include <map>
#include <unordered_map>
#include <set>

namespace critical {

namespace ls {

/**
 * @brief The path table is a data structure that keeps track of the paths of multiple flows. 
 * It is optimized to find out quickly which flows are affected by a link failure. This is achieved 
 * by scattering the path and bundling common links together. 
 * 
 */
class PathTable: public NonCopyable, public Parameterizable {
  private:
    struct FlowData;
    
    struct BundledLinks {
      RouterId routerId;
      int linkId;
      std::set<FlowMapEntry<FlowData>*> entries;

      BundledLinks(const RouterId& routerId, int linkId): routerId(routerId), linkId(linkId) {};

      bool isEmpty() { return entries.empty(); }

      uint64_t estimateMemoryFootprint() const {
        return entries.size() * sizeof(FlowMapEntry<FlowData>*);
      }
    };

    struct FlowData {
      FlowParameters params;
      std::set<BundledLinks*> scatteredPath;
    };

  private:
    LinearFlowMap<FlowData> flowMap;
    std::map<RouterId, std::unordered_map<int, BundledLinks*>> table;
    LinearFlowMap<int> optimizedData;

  public:
    PathTable(CriticalProtocol* protocol);
    virtual ~PathTable();

    /**
     * @brief Clears the full path table
     */
    void clear();

    /**
     * @brief Insert a path in the path table. Since the path will get scattered in this table, 
     * the order of the path is lost. This method expects links of a queue-level topology.
     * 
     * @param flow
     * @param path 
     */
    void insertPath(const Flow& flow, const std::vector<const Topology::Link*>& path);

    /**
     * @brief Removes the path in the flow table.
     * 
     * @param flow 
     */
    void removePath(const FlowId& flow);

    /**
     * @brief Removes all the paths going through the given (broken) link, and returns the flows
     * that were affected.
     * 
     * @param routerId 
     * @param linkId 
     * @return std::vector<FlowData> 
     */
    std::vector<Flow> removeAllGoingThrough(const RouterId& routerId, int linkId);

    uint64_t estimateMemoryFootprint() const {
      uint64_t bytes = flowMapEntries * sizeof(FlowMapEntry<FlowData>);
      bytes += tableEntries * sizeof(FlowMapEntry<FlowData>*);
      //uint64_t bytes = flowMap.size() * sizeof(FlowMapEntry<FlowData>);
      //for (const auto& [_, entries]: table) {
      //  for (const auto& entry: entries) {
      //    bytes += entry.second->estimateMemoryFootprint();
      //  }
      //}
      return bytes;
    }

  private:
    BundledLinks* findOrCreateZippedLink(const RouterId& routerId, int linkId);

    void eraseAndClean(BundledLinks*& bundle);

    bool contains(const RouterId& routerId, int linkId);

  private:
    uint64_t flowMapEntries = 0;
    uint64_t tableEntries = 0;

};

}

}

#endif 