#include "RoutingComponent.h"

#include "critical/CriticalProtocol.h"

namespace critical {

template <class T>
RoutingComponent<T>::RoutingComponent(CriticalProtocol* protocol): ProtocolComponent(protocol) {
  router = nullptr;
};

template <class T>
void RoutingComponent<T>::init() {
  router = check_and_cast<T*>(protocol->getRouter());
};



}

