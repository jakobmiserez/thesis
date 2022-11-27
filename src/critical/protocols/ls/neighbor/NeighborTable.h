#ifndef _CRITICAL_LS_NEIGHBORTABLE_H
#define _CRITICAL_LS_NEIGHBORTABLE_H

#include "critical/protocols/ls/util/LsDefs.h"

#include <inet/networklayer/contract/ipv6/Ipv6Address.h>
#include <inet/networklayer/common/L3AddressResolver.h>
#include <inet/networklayer/ipv6/Ipv6InterfaceData.h>
#include <map>
#include <set>

namespace critical {

namespace ls {

class NeighborTable {
  public:
    struct Neighbor {
      int interfaceId; 
      inet::Ipv6Address network; 
      uint8_t prefixLength;  

      RouterId neighborId;               // to be adjusted when receiving a hello packet
      inet::Ipv6Address neighborAddress; // to be adjusted when receiving a hello packet
      bool helloSent;                    // to be adjusted when sending a hello packt

      Neighbor(): interfaceId(-1) {};
      Neighbor(int interfaceId): interfaceId(interfaceId) {}; 
          
      bool isFullyAdjacent() const {
        return (
          !neighborId.isUnspecified() &&
          !neighborAddress.isUnspecified() && 
          helloSent
        );
      };

      bool isDown() const {
        return (
          !helloSent &&
          neighborId.isUnspecified() &&
          neighborAddress.isUnspecified()
        );
      };

      void goDown() {
        helloSent = false;
        neighborId = inet::Ipv6Address::UNSPECIFIED_ADDRESS;
        neighborAddress = inet::Ipv6Address::UNSPECIFIED_ADDRESS;
      };  
    };

  private:
    std::map<int, Neighbor> table;

  public:
    void addNeighbor(const inet::InterfaceEntry* interface) {
      Neighbor n(interface->getInterfaceId());

      // Network information
      inet::Ipv6InterfaceData* data = interface->findProtocolData<inet::Ipv6InterfaceData>();
      n.prefixLength = data->getAdvPrefix(0).prefixLength;
      n.network = data->getAdvPrefix(0).prefix;

      // Neighbor information
      n.neighborId = inet::Ipv6Address::UNSPECIFIED_ADDRESS;
      n.neighborAddress = inet::Ipv6Address::UNSPECIFIED_ADDRESS;
      n.helloSent = false;

      table[n.interfaceId] = n;
    };

    void sentHello(int interfaceId) {
      Neighbor& n = table[interfaceId];
      n.helloSent = true;
    };

    void setNeighborInfo(
      int interfaceId, 
      const RouterId& neighborId,
      const inet::Ipv6Address& neighborAddress
    ) {
      Neighbor& n = table[interfaceId];
      n.neighborId = neighborId;
      n.neighborAddress = neighborAddress;
    };

    size_t size() const {
      return table.size();
    };

    const Neighbor& getNeighbor(int interfaceId) const {
      return table.at(interfaceId);
    };

    const Neighbor* findNeighbor(const RouterId& routerId) const {
      const Neighbor* res = nullptr;

      auto it = table.begin();
      while (it != table.end() && res == nullptr) {
        const auto& [_, neighbor] = *it;
        if (neighbor.neighborId == routerId) {
          res = &neighbor;
        }
        ++it; 
      }

      return res;
    };

    void goDown(int interfaceId) {
      table.at(interfaceId).goDown();
    };

    size_t getFullyAdjacentCount() const {
      size_t count = 0;
      for (const auto& [_, n]: table) {
        if (n.isFullyAdjacent())
          count++;
      }
      return count;
    };

    size_t getNetworkCount() const {
      size_t count = 0;
      for (const auto& [_, n]: table) {
        if (!n.isFullyAdjacent() && !n.isDown())
          count++;
      }
      return count;
    };

    std::_Rb_tree_const_iterator<std::pair<const int, Neighbor>> begin() const {
      return table.begin();
    };

    std::_Rb_tree_const_iterator<std::pair<const int, Neighbor>> end() const {
      return table.end();
    };

    void print() const {
      inet::L3AddressResolver resolver;
      for (auto [_, entry]: table) {
        if (entry.neighborAddress.isUnspecified()) {
          EV_INFO << "ID: " << entry.interfaceId << " (unspec), down: " << entry.isDown() << "\n";
        }
        else {
          EV_INFO << "ID: " << entry.interfaceId << " " << resolver.findHostWithAddress(entry.neighborAddress) << "\n";
        }
      }
    }
};

}

}


#endif 