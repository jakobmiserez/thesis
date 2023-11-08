#ifndef _CRITICAL_LS_TOPOLOGY_H
#define _CRITICAL_LS_TOPOLOGY_H

#include "critical/protocols/ls/util/LsDefs.h"
#include "critical/common/util/Util.h"
#include "critical/common/util/NonCopyable.h"

#include <functional>
#include <vector>
#include <omnetpp.h>
#include <inet/networklayer/common/L3AddressResolver.h>

using namespace omnetpp;

namespace critical {

namespace ls {

class Topology: public NonCopyable {
  public:
    class Link;
    struct NodePathData {
      int hops;
      double metric;
      double originalMetric;
      bool visited;
      Link* incoming;
      RouterId firstHop;

      void clear() {
        hops = 0;
        metric = INF;
        originalMetric = INF;
        visited = false;
        incoming = nullptr;
        firstHop = inet::Ipv6Address::UNSPECIFIED_ADDRESS;
      };
    };

    class Node {
      private:
        RouterId routerId;
        std::vector<Link> outgoingLinks;

        friend class Topology;
        
        // path computation variables
        NodePathData data;
        
      protected:
        Node(const RouterId& routerId): routerId(routerId) { clear(); };
      public:
        virtual ~Node() {};

        const RouterId& getRouterId() const { return routerId; };
        const NodePathData& getData() const { return data; };
        bool isSubnetNode() const { return routerId.isUnspecified(); };
        bool isReachable() const { return data.metric != INF; };

        const Link* findLink(int linkId) const {
          int i = 0;
          while (i < outgoingLinks.size() && outgoingLinks[i].id != linkId)
            i++;
          if (i == outgoingLinks.size())
            return nullptr;
          return &outgoingLinks[i];
        };

      private:
        void clear() { data.clear(); };
    };

    class RouterNode: public Node {
      public:
        RouterNode(const RouterId& routerId): Node(routerId) {};
        virtual ~RouterNode() {};
    };

    class SubnetNode: public Node {
      private:
        inet::Ipv6Address networkPrefix;
        uint8_t prefixLength;

      public:
        SubnetNode(const inet::Ipv6Address& networkPrefix, uint8_t prefixLength)
        : Node(inet::Ipv6Address::UNSPECIFIED_ADDRESS),
          networkPrefix(networkPrefix),
          prefixLength(prefixLength) {};
        virtual ~SubnetNode() {};

        bool isDestinationFor(const inet::Ipv6Address& dest) const {
          if (dest.isUnspecified()) {
            return false;
          }
          return dest.matches(networkPrefix, (int)prefixLength);
        };
        const inet::Ipv6Address& getNetworkPrefix() const { return networkPrefix; };
        uint8_t getPrefixLength() const { return prefixLength; };
    };

    class Link {
      private:
        int id;
        Node* from;
        Node* to;
        double cost;

        friend class Topology;
      
      public:
        Link(int id, Node* from, Node* to, double cost): id(id), from(from), to(to), cost(cost) {};
        ~Link() {};

        const Node* getFrom() const { return from; };
        const Node* getTo() const { return to; };
        int getId() const { return id; };
        double getCost() const { return cost; };
    };

    template <class T>
    struct QueuedNode {
      Node* node;
      double metric;
      T params;

      friend bool operator>(const QueuedNode& lhs, const QueuedNode& rhs) {
        return lhs.metric > rhs.metric;
      };  
    };

    template <class T>
    struct PathAccessControl {
      virtual bool canAccessLink(const Link& link, const QueuedNode<T>& node) const = 0;
      virtual T updateAfterAccess(const Link& link, const QueuedNode<T>& node) const = 0;
    };

    struct NoAccessControl: public PathAccessControl<Empty> {
      virtual bool canAccessLink(const Link& link, const QueuedNode<Empty>& node) const override { return true; };
      virtual Empty updateAfterAccess(const Link& link, const QueuedNode<Empty>& node) const override { return node.params; };
    };

    private:
      std::map<RouterId, RouterNode*> routerNodes;
      std::set<SubnetNode*> subnetNodes;
      std::vector<const Link*> path;
      size_t links;

      static std::function<double(const Link&)> DEFAULT_COST_FUNCTION;
      static Empty INITIAL_NO_ACCESS_CONTROL;
      static NoAccessControl NO_ACCESS_CONTROL;

    public:
      Topology();
      virtual ~Topology();

      void clear();

      const std::vector<const Link*>& getPath() const { return path; };
      std::set<SubnetNode*> getSubnetNodes() { return subnetNodes; };
      void print() const;
      void printPath() const;

      uint64_t computeMemoryFootprint() const;

    protected:
      Node* addRouterNode(const RouterId& routerId);
      Node* addRouterNodeIfNotExists(const RouterId& routerId);
      Node* addSubnetNode(const inet::Ipv6Address& networkPrefix, uint8_t prefixLength);

      void addLink(int id, Node* from, Node* to, double cost);

      template <class T>
      void computeDistances(Node* from, T initial, const PathAccessControl<T>& accessControl, std::function<double(const Link&)> costf);
      template <class T>
      void computeDistances(Node* from, T initial, const PathAccessControl<T>& accessControl);
      void computeDistances(Node* from, std::function<double(const Link&)> costf);
      void computeDistances(Node* from);
      
      template <class T>
      void computeDistance(Node* from, Node* to, T initial, const PathAccessControl<T>& accessControl, std::function<double(const Link&)> costf);
      template <class T>
      void computeDistance(Node* from, Node* to, T initial, const PathAccessControl<T>& accessControl);
      void computeDistance(Node* from, Node* to, std::function<double(const Link&)> costf);
      void computeDistance(Node* from, Node* to);


      Node* getNodeWithId(const RouterId& RouterId) const;
      Node* getDestinationNode(const inet::Ipv6Address& destination) const;

    private:
      void buildPath(Node* from, Node* to);
};

}

}

#endif 