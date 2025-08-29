#ifndef _CRITICAL_EXPALLOCATOR_H
#define _CRITICAL_EXPALLOCATOR_H

#include "IBudgetAllocator.h"

#include <math.h>

namespace critical {

/**
 * Difference between previous queues grows exponentially
 **/
class ExpAllocator: public IBudgetAllocator {
  public:
    ExpAllocator(uint64_t start, uint64_t diff, uint64_t factor): start(start), diff(diff), factor(factor) {
      budgets[0] = start;
      
      for (int i = 1; i < 8; i++) {
        budgets[i] = budgets[i-1] + diff;
        diff = diff * factor;
      }
    };
  
    virtual bool check(int numQueues) override {
      return numQueues == 8;
    };

    virtual uint64_t allocate(int queue, int numQueues) override {
      return budgets[queue];
     //if (queue == 0)
     //  return start;
     //return start + diff * pow(factor, queue - 1);
    };

  private:
    uint64_t start;
    uint64_t diff;
    uint64_t factor;

    uint64_t budgets[8];
};

}


#endif 