#ifndef _CRITICAL_MODULEHELPERS_H
#define _CRITICAL_MODULEHELPERS_H

#include <inet/networklayer/common/InterfaceEntry.h>
#include <omnetpp.h>

using namespace omnetpp;

namespace critical {

class ModuleHelpers {

  public:
    static cModule* getOutgoingModule(const inet::InterfaceEntry* entry) {
      int gateId = entry->getNodeOutputGateId();
      cGate* gate = entry->getParentModule()->gate(gateId);
      cGate* end = gate->getNextGate();

      while (end->getNextGate() != nullptr) {
        end = end->getNextGate();
      }

      return end->getOwnerModule();
    };

    static cModule* getOutgoingNetworkNode(const inet::InterfaceEntry* entry) {
      int gateId = entry->getNodeOutputGateId();
      cGate* gate = entry->getParentModule()->gate(gateId);
      cGate* end = gate->getNextGate();

      while (end->getNextGate() != nullptr) {
        end = end->getNextGate();
      }

      return findParentNetworkNode(end->getOwnerModule());
    }

    static cModule* findParentNetworkNode(cModule* mod) {
      cModule* current = mod;
      while (current != nullptr && !current->getProperties()->getAsBool("networkNode")) {
        current = current->getParentModule();
      }
      return current;
    }

    static cModule* getOutgoingModule(const inet::InterfaceEntry* entry, int depth) {
      int gateId = entry->getNodeOutputGateId();
      cGate* gate = entry->getParentModule()->gate(gateId);
      cGate* end = gate->getNextGate();

      int i = 0;
      while (end->getNextGate() != nullptr && i < depth) {
        end = end->getNextGate();
        i++;
      }

      return end->getOwnerModule();
    }

    static cChannel* getChannel(const inet::InterfaceEntry* entry) {
      int gateId = entry->getNodeOutputGateId();
      cGate* gate = entry->getParentModule()->gate(gateId);

      return gate->getTransmissionChannel();
    };

    static cObject* resolveNodeWithName(cModule* mod, const char* name) {
      return mod->findObject(name, true);
    }
};

}

#endif 