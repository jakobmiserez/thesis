#include "LsaDatabase.h"

#include "critical/protocols/ls/LsRouter.h"
#include "critical/common/util/Util.h"

namespace critical {

namespace ls {

LsaDatabase::LsaDatabase() {

}

LsaDatabase::~LsaDatabase() {

}

bool LsaDatabase::insertLsa(const LsaPacket* const lsaPacket) {
  Lsa lsa = toLsa(lsaPacket);
  EV_INFO << "(LSA DATABASE) Received LSA of " << inet::L3AddressResolver().findHostWithAddress(lsa.id)->getName() << "\n";

  const auto& it = map.find(lsa.id);
  if (it != map.end()) {
    const auto& existingEntry = it->second;
    if (existingEntry.sequenceNumber < lsa.sequenceNumber) {
      auto connectivityChanges = getConnectivityChanges(existingEntry, lsa);
      map[lsa.id] = lsa;

      EV_INFO << "(LSA DATABASE) Overrided entry in LSA database ("  << map.size() << ")\n";
      EV_INFO << "(LSA DATABASE) Connectivity has changed: " << connectivityChanges.connectivityChanged() << "\n";
      EV_INFO << "(LSA DATABASE) New number of links: " << lsa.links.size() << "\n";

      notifyListeners([lsa, connectivityChanges](LsaListener* l) { l->onLsaUpdate(lsa, connectivityChanges); });
      return true;
    }
    
    EV_INFO << "(LSA DATABASE) Ignoring outdated LSA ("  << map.size() << ")\n";
    return false;
  }

  map[lsa.id] = lsa;
  EV_INFO << "(LSA DATABASE) Inserted new entry in LSA database ("  << map.size() << ")\n";
  
  notifyListeners([lsa](LsaListener* l) { l->onLsaAdded(lsa); });
  return true;
}

Lsa LsaDatabase::toLsa(const LsaPacket* const lsaPacket) {
  Lsa lsa;
  lsa.id = lsaPacket->getRouterId();
  lsa.sequenceNumber = lsaPacket->getSequenceNumber();

  uint64_t chunkLength = (lsaPacket->getChunkLength().get() / 8) - 22;

  uint8_t numNetworkEntries = lsaPacket->getNetworkEntriesCount();
  uint8_t numNeighborEntries = (chunkLength - (numNetworkEntries * 20)) / 53;

  //EV_INFO << "Chunklength: " << chunkLength << "\n";
  //EV_INFO << "Check: " << lsaPacket->getChunkLength() << "\n";
  //EV_INFO << "numNetworkEntries:  " << (int)numNetworkEntries << "\n";
  //EV_INFO << "numNeighborEntries: " << (int)numNeighborEntries << "\n";

  
  lsa.links.reserve(numNeighborEntries + numNetworkEntries);
  for (uint8_t i = 0; i < numNeighborEntries; i++) {
    LinkStateNeighborEntry entry = lsaPacket->getNeighborEntries(i);

    Lsa::Link n;
    n.networkAddress = entry.getNetwork();
    n.prefixLength = entry.getPrefixLength();
    n.to = entry.getNeighborId();
    n.cost = entry.getCost();
    n.bw = entry.getBw();
    n.delay = entry.getDelay();
    n.linkId = entry.getLinkId();
    n.numQueues = entry.getNumQueues();

    lsa.links.push_back(n);
  }

  for (uint8_t i = 0; i < numNetworkEntries; i++) {
    LinkStateNetworkEntry entry = lsaPacket->getNetworkEntries(i);

    Lsa::Link n;
    n.networkAddress = entry.getNetwork();
    n.prefixLength = entry.getPrefixLength();
    n.to = inet::Ipv6Address::UNSPECIFIED_ADDRESS;
    n.cost = 1;
    n.bw = 0xffffffffffffffff; // set bw to max value TODO
    n.delay = 0;
    n.linkId = entry.getLinkId();
    n.numQueues = entry.getNumQueues();
  
    lsa.links.push_back(n);
  }
  
  return lsa;
}

const Lsa& LsaDatabase::getLsaOf(const RouterId& routerId) const {
  return map.at(routerId);
}

LsaConnectivityChanges LsaDatabase::getConnectivityChanges(const Lsa& oldLsa, const Lsa& newLsa) {
  std::set<int> addedLinks;
  std::set<int> removedLinks;

  std::set<RouterId> newNeighbors = newLsa.constructNeighborSet();
  std::set<RouterId> oldNeighbors = oldLsa.constructNeighborSet();

  // Find the links that were added 
  for (const auto& link: newLsa.links) {
    if (link.isLinkToRouter() && !contains(oldNeighbors, link.to)) {
      addedLinks.emplace(link.linkId);
    }
  }

  // Find the links that were deleted
  for (const auto& link: oldLsa.links) {
    if (link.isLinkToRouter() && !contains(newNeighbors, link.to)) {
      removedLinks.emplace(link.linkId);
    }
  }

  return { addedLinks, removedLinks };
}

}

}