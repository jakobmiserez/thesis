#ifndef _CRITICAL_ROUTINGCOMPONENT 
#define _CRITICAL_ROUTINGCOMPONENT

#include "ProtocolComponent.h"
#include <omnetpp.h>

using namespace omnetpp;

namespace critical {

template <class T>
class RoutingComponent: public ProtocolComponent {
  protected:
    T* router;

  public:
    RoutingComponent(CriticalProtocol* protocol);

    void init();

    virtual ~RoutingComponent() {};

};

}

#include "RoutingComponent.tcc"

#endif