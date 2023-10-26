#ifndef _CRITICAL_LINEARALLOCATOR_H
#define _CRITICAL_LINEARALLOCATOR_H

#include "IBudgetAllocator.h"

namespace critical {

class LinearAllocator: public IBudgetAllocator {
  public:
    LinearAllocator(uint64_t start, uint64_t diff, uint64_t factor) {
      budgets[0] = start;
      for (int i = 1; i < 8; i++, diff += factor) {
        budgets[i] = budgets[i-1] + diff;
      }
    };

    virtual bool check(int numQueues) override {
        return numQueues == 8;
    }

    virtual uint64_t allocate(int queue, int numQueues) override {
        //if (queue == 0)
        //    return start;
        //return start + (diff + (queue - 1) * factor);
      return budgets[queue];
    }

  private:
    uint64_t start;
    uint64_t diff;
    uint64_t factor;

    uint64_t budgets[8];
};

}


#endif 