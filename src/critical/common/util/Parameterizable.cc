#include "Parameterizable.h"

#include "critical/CriticalProtocol.h"

namespace critical {

Parameterizable::Parameterizable(CriticalProtocol* protocol)
: ProtocolComponent(protocol) {
  
}

Parameterizable::~Parameterizable() {
  
}

const CriticalProtocolParameters& Parameterizable::getParams() const {
  return protocol->getParams();
}

double Parameterizable::getDoubleParam(const char* name) const {
  return protocol->par(name).doubleValue();
}

int Parameterizable::getIntParam(const char* name) const {
  return protocol->par(name).intValue();
}

}