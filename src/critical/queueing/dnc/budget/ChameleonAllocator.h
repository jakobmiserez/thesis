#ifndef _CRITICAL_CHAMELEONALLOCATOR_H
#define _CRITICAL_CHAMELEONALLOCATOR_H

#include "IBudgetAllocator.h"

namespace critical {

class ChameleonAllocator: public IBudgetAllocator {

  private:
    static const uint64_t budgets2[2];
    static const uint64_t budgets4[4];
    static const uint64_t budgets8[8];

  public:
    virtual bool check(int numQueues) override;

    virtual uint64_t allocate(int queue, int numQueues) override;
};

}


#endif 