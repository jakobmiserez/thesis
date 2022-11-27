#ifndef _CRITICAL_CUSTOMALLOCATOR_H
#define _CRITICAL_CUSTOMALLOCATOR_H

#include "IBudgetAllocator.h"

namespace critical {

class CustomAllocator: public IBudgetAllocator {

  private:
    static const uint64_t budgets4[4];
    static const uint64_t budgets8[8];

  public:
    virtual bool check(int numQueues) override;

    virtual uint64_t allocate(int queue, int numQueues) override;
};

}


#endif 