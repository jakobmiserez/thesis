#ifndef _CRITICAL_LS_LSADATABASE_H
#define _CRITICAL_LS_LSADATABASE_H

#include "critical/protocols/ls/packets/LsPackets_m.h"
#include "critical/protocols/ls/util/LsDefs.h"
#include "critical/common/util/Observable.h"

#include <functional>
#include <map>
#include <vector>

namespace critical {

namespace ls {

class LsRouter;

struct Lsa {
  struct Link {
    inet::Ipv6Address networkAddress;
    uint8_t prefixLength;
    int linkId;
    int numQueues;

    uint64_t delay;
    uint64_t bw;

    RouterId to;
    uint8_t cost;

    bool isLinkToRouter() const { return !to.isUnspecified(); };
  };

  //std::vector<RouterNeighborLink> neighborLinks;
  std::vector<Link> links;
  uint32_t sequenceNumber;
  RouterId id;

  bool hasNeighbor(const RouterId& neighbor) const {
    int i = 0;
    while (i < links.size() && links[i].to != neighbor) {
      i++;
    }
    return i < links.size();
  };

  size_t numTotalLinks() const {
    return links.size();
  };

  std::set<RouterId> constructNeighborSet() const {
    std::set<RouterId> res;
    for (auto n: links) {
      if (n.isLinkToRouter())
        res.insert(n.to);
    }
    return res;
  };
};

struct LsaConnectivityChanges {
  std::set<int> addedLinks;
  std::set<int> removedLinks;

  bool connectivityChanged() const { return addedLinks.size() > 0 || removedLinks.size() > 0; };
};

struct LsaListener {
  virtual void onLsaAdded(const Lsa& lsa) = 0;
  virtual void onLsaUpdate(const Lsa& lsa, const LsaConnectivityChanges& connectivity) = 0;
};

class LsaDatabase: public Observable<LsaListener> {
  private:
    std::map<RouterId, Lsa> map;

  public:
    LsaDatabase();
    virtual ~LsaDatabase();

    bool insertLsa(const LsaPacket* const lsaPacket);
    size_t size() const { return map.size(); };
    const Lsa& getLsaOf(const RouterId& routerId) const;

    std::_Rb_tree_const_iterator<std::pair<const RouterId, Lsa>> begin() const {
      return map.begin();
    };

    std::_Rb_tree_const_iterator<std::pair<const RouterId, Lsa>> end() const {
      return map.end();
    };

    const Lsa& operator[](const RouterId& id) {
      return map[id];
    };

  private:
    Lsa toLsa(const LsaPacket* const lsaPacket);

    LsaConnectivityChanges getConnectivityChanges(const Lsa& oldLsa, const Lsa& newLsa);

};

}

}


#endif 