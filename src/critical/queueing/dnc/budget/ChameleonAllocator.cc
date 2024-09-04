#include "ChameleonAllocator.h"

#include <omnetpp.h>

using namespace omnetpp;

namespace critical {

const uint64_t ChameleonAllocator::budgets2[2] = { 500, 3000 };
const uint64_t ChameleonAllocator::budgets4[4] = { 100, 1000, 6000, 24000 };
const uint64_t ChameleonAllocator::budgets8[8] = { 100, 500,  1000, 1500, 3000, 6000, 12000, 24000 };

bool ChameleonAllocator::check(int numQueues) {
  switch (numQueues) {
    case 2:
    case 4:
    case 8:
      return true;
    default:
      return false;
  }
}

uint64_t ChameleonAllocator::allocate(int queue, int numQueues) {
  switch (numQueues) {
    case 2:
      return budgets2[queue];
    case 4:
      return budgets4[queue];
    case 8:
      return budgets8[queue];
    default:
      throw cRuntimeError("Unsupported number of QoS queues: %i", numQueues);
  }
}


}