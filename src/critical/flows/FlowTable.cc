#include "FlowTable.h"

#include "critical/flows/map/linear/LinearFlowMap.h"

namespace critical {

FlowTable::FlowTable() {
  flowMap = new LinearFlowMap<FlowTableData>();
}

FlowTable::~FlowTable() {
  delete flowMap;
}

FlowTableEntry& FlowTable::embedFlow(
  const FlowId id,
  const FlowParameters params,
  int interface, 
  const inet::L3Address& nextHop,
  int prevInterface,
  int queueNumber,
  bool isFinalHop,
  bool isFirstHop,
  bool confirmed
) {
  FlowTableData data(params, interface, prevInterface, nextHop, queueNumber);
  data.firstHop = isFirstHop;
  data.finalHop = isFinalHop;
  data.confirmed = confirmed;
  auto entry = flowMap->insertFlow(id, data);

  EV_INFO << "(FLOW TABLE) Inserting flow: " << id << "\n";

  if (confirmed) {
     onConfirm(entry);
  }
  
  return *entry;
}

FlowTableEntry* FlowTable::lookup(const inet::L3Address& src, const inet::L3Address& dest, uint32_t label) {
  return flowMap->lookupFlow(FlowId(src, dest, label));
}

FlowTableEntry* FlowTable::confirm(const FlowId& flow) {
  auto* entry = flowMap->lookupFlow(flow);
  if (entry == nullptr) {
    throw cRuntimeError("Cannot confirm a non-existent entry");
  }
  bool alreadyConfirmed = entry->data.confirmed;
  if (!alreadyConfirmed) {
    entry->data.confirmed = true;
    onConfirm(entry);
  }
  return entry;
}

FlowTableEntry FlowTable::deleteFlow(const inet::L3Address& src, const inet::L3Address& dest, uint32_t label) {
  EV_INFO << "(FLOW TABLE) Deleting flow: " << FlowId(src, dest, label) << "\n";
  
  FlowTableEntry* ptr = flowMap->removeFlow(FlowId(src, dest, label));
  
  onDelete(ptr);
  FlowTableEntry copy = *ptr;
  delete ptr;
  
  return copy;
}

void FlowTable::onConfirm(const FlowTableEntry* entry) {
  notifyListeners([entry](IFlowTableListener* l) { l->onFlowAccepted(entry); });
}

void FlowTable::onDelete(const FlowTableEntry* entry) {
  notifyListeners([entry](IFlowTableListener* l) { l->onFlowDelete(entry); });
}

uint64_t FlowTable::estimateMemoryFootprint() const {
  return flowMap->size() * sizeof(FlowTableEntry);
}

}

