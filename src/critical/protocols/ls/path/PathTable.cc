#include "PathTable.h"

#include "critical/protocols/ls/topology/QueueLevelTopologyLinkEncoding.h"
#include <omnetpp.h>

using namespace omnetpp;

namespace critical {

namespace ls {

PathTable::~PathTable() {
  clear();
}

void PathTable::clear() {
  for (auto& [_, nodeMap]: table) {
    for (auto& [_, bundle]: nodeMap) {
      delete bundle;
    }
    nodeMap.clear();
  }
  table.clear();
}

void PathTable::insertPath(const Flow& flow, const std::vector<const Topology::Link*>& path) {
  EV_INFO << "(PATH TABLE) Inserting path\n";

  FlowMapEntry<FlowData>* entry = flowMap.insertFlow(flow.id, { flow.params });
  for (const auto& link: path) {
    int linkId = QueueLevelTopologyLinkEncoding::getLinkId(link->getId());

    BundledLinks* bundle = findOrCreateZippedLink(link->getFrom()->getRouterId(), linkId);
    bundle->entries.insert(entry);

    entry->data.scatteredPath.insert(bundle);
  }
};

void PathTable::removePath(const FlowId& flow) {
  EV_INFO << "(PATH TABLE) Removing path\n";
  FlowMapEntry<FlowData>* entry = flowMap.lookupFlow(flow);
  for (auto bundle: entry->data.scatteredPath) {
    bundle->entries.erase(entry);
    eraseAndClean(bundle);
  }
  flowMap.deleteFlow(flow);
}

std::vector<Flow> PathTable::removeAllGoingThrough(const RouterId& routerId, int linkId) {
  EV_INFO << "(PATH TABLE) Removing all paths going through a link\n";
  std::vector<Flow> flows;

  // Find the bundle of broken links
  if (!contains(routerId, linkId)) {
    EV_INFO << "(PATH TABLE) Removed " << flows.size() << " flows\n";
    return flows;
  }
  BundledLinks* brokenBundle = table.at(routerId).at(linkId);
  flows.reserve(brokenBundle->entries.size());

  // For every broken path, we find the flow that was associated with 
  // the path and delete the flow and path from the table
  for (const auto& entry: brokenBundle->entries) {
    
    // Keep track of the flows were the path is deleted
    flows.emplace_back(entry->flow, entry->data.params);

    // Delete the flow from the flow map
    auto deletedEntry = flowMap.deleteFlow(entry->flow);

    // Clean the full path
    for (auto bundle: deletedEntry.data.scatteredPath) {
      // Don't clean up the broken bundle, as we are iterating 
      // over its entries
      if (bundle == brokenBundle) {
        continue;
      }

      // Clean up this entry
      bundle->entries.erase(entry);

      // Clean up as much as pssible
      eraseAndClean(bundle);
    }
  }

  // Clean up the broken bundle
  brokenBundle->entries.clear();
  eraseAndClean(brokenBundle);

  EV_INFO << "(PATH TABLE) Removed " << flows.size() << " flows\n";
  return flows;
}

PathTable::BundledLinks* PathTable::findOrCreateZippedLink(const RouterId& routerId, int linkId) {
  auto& nodeMap = table[routerId];
  auto it2 = nodeMap.find(linkId);
  if (it2 != nodeMap.end()) {
    return it2->second;
  }

  BundledLinks* zippedLink = new BundledLinks(routerId, linkId);
  nodeMap[linkId] = zippedLink;
  return zippedLink;
}

void PathTable::eraseAndClean(BundledLinks*& bundle) {
  if (!bundle->isEmpty()) {
    return;
  }

  auto& nodeMap = table.at(bundle->routerId);
  nodeMap.erase(bundle->linkId);

  if (nodeMap.empty()) {
    table.erase(bundle->routerId);
  }

  delete bundle;
  bundle = nullptr;
}

bool PathTable::contains(const RouterId& routerId, int linkId) {
  auto it = table.find(routerId);
  if (it == table.end()) {
    return false;
  }
  auto it2 = it->second.find(linkId);
  if (it2 == it->second.end()) {
    return false;
  }
  return true;
}

}


}