#ifndef _CRITICAL_BUDGETALLOCATORFACTORY_H
#define _CRITICAL_BUDGETALLOCATORFACTORY_H

#include "ChameleonAllocator.h"
#include "CustomAllocator.h"
#include "ExponentialAllocator.h"
#include "LinearAllocator.h"
#include "ConstantAllocator.h"

#include "critical/parameters/CriticalProtocolParameters.h"

#include <omnetpp.h>
#include <string>

using namespace omnetpp;

namespace critical {

class BudgetAllocatorFactory {
  public:
    static IBudgetAllocator* createNewAllocator(const BudgetAllocator& allocator) {
      switch (allocator) {
        case CHAMELEON:
          return new ChameleonAllocator();
        case CUSTOM:
        case CONST1:
        case EXP:
        case GAP:
        case INCREASING1:
        case INCREASING2:
        case SIMPLE1:
        case SIMPLE2:
        case SIMPLE3:
        case QOPT1:
        case QOPTDISTRANDOM:
        case QOPTDISTVIDEO40:
        case QOPTDISTVIDEO60:
        case QOPTDISTVIDEO80:
        case QOPTDISTVIDEO100:
          return new CustomAllocator(allocator);
        //case CHAMELEON:
          //return new ChameleonAllocator();
        
        case EXP_DIFF_100_100_2:
          return new ExpAllocator(100, 100, 2);

        case LINEAR_DIFF_100_200_100:
          return new LinearAllocator(100, 200, 100);
        case LINEAR_DIFF_100_400_200:
          return new LinearAllocator(100, 400, 200);

        case CONSTANT_DIFF_50_100:
          return new ConstantAllocator(50, 100);
        case CONSTANT_DIFF_50_200:
          return new ConstantAllocator(50, 200);
        case CONSTANT_DIFF_100_500:
          return new ConstantAllocator(100, 500);
        case CONSTANT_DIFF_500_500:
          return new ConstantAllocator(500, 500);
        case CONSTANT_DIFF_100_0:
          return new ConstantAllocator(100, 0);
        case CONSTANT_DIFF_500_0:
          return new ConstantAllocator(500, 0);
        case CONSTANT_DIFF_1000_0:
          return new ConstantAllocator(1000, 0);
        default:
          throw cRuntimeError("Unavailable allocator");
      }
    };
};

}


#endif 