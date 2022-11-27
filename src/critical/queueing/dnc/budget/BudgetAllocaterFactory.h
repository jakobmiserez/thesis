#ifndef _CRITICAL_BUDGETALLOCATORFACTORY_H
#define _CRITICAL_BUDGETALLOCATORFACTORY_H

#include "ChameleonAllocator.h"
#include "CustomAllocator.h"
#include "critical/parameters/CriticalProtocolParameters.h"

#include <omnetpp.h>
#include <string>

using namespace omnetpp;

namespace critical {

class BudgetAllocatorFactory {
  public:
    static IBudgetAllocator* createNewAllocator(const BudgetAllocator& allocator) {
      switch (allocator) {
        case CUSTOM:
          return new CustomAllocator();
        case CHAMELEON:
        default:
          return new ChameleonAllocator();
      }
    };
};

}


#endif 