#include "LinearFlowMap.h"

namespace critical {

template <class T>
LinearFlowMap<T>::LinearFlowMap() {

}

template <class T>
LinearFlowMap<T>::~LinearFlowMap() {

}

template <class T>
void LinearFlowMap<T>::clear() {
  for (const auto ptr: entries) {
    delete ptr;
  }
  entries.clear();
}

template <class T>
FlowMapEntry<T>* LinearFlowMap<T>::insertFlow(const FlowId& flow, T data) {
  if (lookupFlow(flow) != nullptr) {
    throw new cRuntimeError("Cannot insert the same flow twice");
  }
  FlowMapEntry<T>* entry = new FlowMapEntry<T>(flow, data);  
  return entries.emplace_back(entry); 
}

template <class T>
FlowMapEntry<T> LinearFlowMap<T>::deleteFlow(const FlowId& flow) {
  auto entry = deleteFlowIfPresent(flow);
  if (!entry.has_value()) {
    throw cRuntimeError("Cannot delete non-existent flow");
  }
  return entry.value();
}

template <class T>
std::optional<FlowMapEntry<T>> LinearFlowMap<T>::deleteFlowIfPresent(const FlowId& flow) {
  int i = indexOf(flow);
  if (i < 0) {
    return {};
  }
  FlowMapEntry<T> entry(*entries[i]);
  delete entries[i];
  entries.erase(entries.begin() + i);
  return entry;
}

template <class T>
FlowMapEntry<T>* LinearFlowMap<T>::lookupFlow(const FlowId& flow) {
  int i = indexOf(flow);
  if (i < 0) {
    return nullptr;
  }
  return entries[i];
}

template <class T>
FlowMapEntry<T>* LinearFlowMap<T>::removeFlow(const FlowId& flow) {
  int i = indexOf(flow);
  if (i < 0) {
    throw cRuntimeError("Cannot remove non-existent flow");
  }
  FlowMapEntry<T>* res = entries[i];
  entries.erase(entries.begin() + i);
  return res;
}

template <class T>
FlowMapEntry<T>* LinearFlowMap<T>::insertIfAbsent(const FlowId& flow, T data) {
  int i = indexOf(flow);
  if (i < 0) 
    return insertFlow(flow, data);
  return entries[i];
}

template <class T>
int LinearFlowMap<T>::indexOf(const FlowId& flow) const {
  int i = 0;
  while (i < entries.size() && entries[i]->flow != flow) {
    i++;
  }
  if (i == entries.size()) {
    return -1;
  }
  return i;
}

template <class T>
size_t LinearFlowMap<T>::size() const {
  return entries.size();
}

}