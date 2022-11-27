#ifndef _CRITICAL_IBUDGETALLOCATOR_H
#define _CRITICAL_IBUDGETALLOCATOR_H

#include <stdint.h>

namespace critical {

class IBudgetAllocator {
  public:
    virtual ~IBudgetAllocator() {};

    virtual bool check(int numQueues) = 0;
    
    /**
     * @brief Allocate a budget to the queue
     * 
     * @param queue 
     * @param numQueues 
     * @return uint64_t The budget in microseconds
     */
    virtual uint64_t allocate(int queue, int numQueues) = 0;
};

}


#endif 