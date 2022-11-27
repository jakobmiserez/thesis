#ifndef _CRITICAL_PARAMETERIZABLE_H
#define _CRITICAL_PARAMETERIZABLE_H

#include <omnetpp.h>
#include "critical/common/util/ProtocolComponent.h"
#include "critical/parameters/CriticalProtocolParameters.h"

using namespace omnetpp;

namespace critical {

class CriticalProtocol;

class Parameterizable: public ProtocolComponent {
  public:
    Parameterizable(CriticalProtocol* protocol);
    virtual ~Parameterizable();

  protected:
    const CriticalProtocolParameters& getParams() const;
    double getDoubleParam(const char* param) const;
    int getIntParam(const char* param) const;
};

}

#endif