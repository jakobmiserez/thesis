#ifndef _CRITICAL_FLOW_H
#define _CRITICAL_FLOW_H

#include <inet/networklayer/common/L3Address.h>
#include <inet/networklayer/common/L3AddressResolver.h>

#include "critical/queueing/dnc/curves/AffineArrivalCurve.h"

namespace critical {

// 36 bytes
struct FlowId {
  inet::Ipv6Address src;
  inet::Ipv6Address dest; 
  uint32_t label;

  FlowId(
    const inet::L3Address& source,
    const inet::L3Address& destination, 
    uint32_t label
  ) : 
    src(source.toIpv6()), 
    dest(destination.toIpv6()), 
    label(label) {};

  FlowId(): src(inet::Ipv6Address::UNSPECIFIED_ADDRESS), dest(inet::Ipv6Address::UNSPECIFIED_ADDRESS), label(0) {};

  bool operator==(const FlowId& other) const {
    return label == other.label && src == other.src && dest == other.dest;
  };

  bool operator!=(const FlowId& other) const {
    return !operator==(other);
  };

  friend std::ostream& operator<<(std::ostream& os, const FlowId& flow);
};

inline std::ostream& operator<<(std::ostream& os, const FlowId& flow) {
  inet::L3AddressResolver resolver;
  os << "FlowId(" << resolver.findHostWithAddress(flow.src)->getFullPath() << "," << flow.label << "," << resolver.findHostWithAddress(flow.dest)->getFullPath() << ")";
  return os;
};

// 24 bytes 
struct FlowParameters {
  uint64_t delay;
  uint64_t rate;
  uint64_t burst;

  FlowParameters(): delay(0), rate(0), burst(0) {};
  FlowParameters(uint64_t delay, uint64_t rate, uint64_t burst) : 
    delay(delay), rate(rate), burst(burst) {};

  AffineArrivalCurve dncModel() const {
    return AffineArrivalCurve(rate, burst);
  };

  static FlowParameters DEFAULT_PARAMS() {
    return FlowParameters(0, 0, 0);
  };
};

// 60 bytes
struct Flow {
  FlowId id;
  FlowParameters params;

  Flow() {};
  Flow(
    const inet::L3Address& source, 
    const inet::L3Address& destination, 
    uint32_t label, 
    uint64_t delay, 
    uint64_t rate, 
    uint64_t burst
  ) : id(source, destination, label), params(delay, rate, burst) {};
  Flow(const FlowId id, const FlowParameters params) : id(id), params(params) {};
  Flow(const Flow& flow) :
    id(flow.id), params(flow.params) {};

  AffineArrivalCurve dncModel() const {
    return params.dncModel();
  };

  Flow& operator=(const Flow& flow) {
    id = flow.id;
    params = flow.params;
    return *this;
  };

  static AffineArrivalCurve dncModel(uint64_t rate, uint64_t burst) {
    return AffineArrivalCurve(rate, burst);
  };

  friend std::ostream& operator<<(std::ostream& os, const FlowParameters& params);
};

inline std::ostream& operator<<(std::ostream& os, const FlowParameters& params) {
  os << "FlowParameters(" << params.delay << "," << params.rate << "," << params.burst << ")";
  return os;
};

}

#endif