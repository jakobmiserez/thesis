#include "CustomAllocator.h"

#include <omnetpp.h>

using namespace omnetpp;

namespace critical {

const uint64_t CustomAllocator::budgets4[4] = { 100, 250, 500, 1000 };
//const uint64_t CustomAllocator::budgets8[8] = { 100, 250, 500, 750, 1000, 3000, 6000, 12000 };
//const uint64_t CustomAllocator::budgets8[8] = { 50, 100, 150, 200, 400, 800, 1600, 3200 };
const uint64_t CustomAllocator::budgets8[8] = { 100, 500, 1000, 2000, 4000, 8000, 16000, 32000 };

bool CustomAllocator::check(int numQueues) {
  switch (numQueues) {
    case 4:
    case 8:
      return true;
    default:
      return false;
  }
}

uint64_t CustomAllocator::allocate(int queue, int numQueues) {
  switch (numQueues) {
    case 4:
      return budgets4[queue];
    case 8:
      return budgets8[queue];
    default:
      throw cRuntimeError("Unsupported number of QoS queues: %i", numQueues);
  }
}


}