#ifndef _CRITICAL_CONSTANTALLOCATOR_H
#define _CRITICAL_CONSTANTALLOCATOR_H

#include "IBudgetAllocator.h"

namespace critical {

/**
 * Difference between previous queues remains constant
 **/
class ConstantAllocator: public IBudgetAllocator {
  public:
    ConstantAllocator(uint64_t start, uint64_t diff): start(start), diff(diff) {};
    ConstantAllocator(): start(500), diff(500) {};

    virtual bool check(int numQueues) override {
      return numQueues == 8;
    };

    virtual uint64_t allocate(int queue, int numQueues) override {
      return start + queue * diff;
    };

  private:
    uint64_t start;
    uint64_t diff;
};

}


#endif 