#include "StatefulMessageHandler.h"

namespace critical {

template <class T>
StatefulMessageHandler<T>::StatefulMessageHandler(CriticalProtocol* const protocol, T initialState) 
  : StatelessMessageHandler(protocol), state(initialState) {

}

template <class T>
StatefulMessageHandler<T>::~StatefulMessageHandler() {

}
  
} 
