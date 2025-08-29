#ifndef _CRITICAL_CUSTOMALLOCATOR_H
#define _CRITICAL_CUSTOMALLOCATOR_H

#include "IBudgetAllocator.h"

#include "critical/parameters/CriticalProtocolParameters.h"

namespace critical {

class CustomAllocator: public IBudgetAllocator {

  private:
    BudgetAllocator custom;
    static const uint64_t budgets2[16][2];
    static const uint64_t budgets4[11][4];
    static const uint64_t budgets8[11][8];

  public:
    CustomAllocator(BudgetAllocator allocator): custom(allocator) {};
    virtual bool check(int numQueues) override;

    virtual uint64_t allocate(int queue, int numQueues) override;
};

}


#endif 