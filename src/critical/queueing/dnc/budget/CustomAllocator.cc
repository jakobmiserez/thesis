#include "CustomAllocator.h"

#include <omnetpp.h>

using namespace omnetpp;

namespace critical {

const uint64_t CustomAllocator::budgets4[4] = { 100, 250, 500, 1000 };
//const uint64_t CustomAllocator::budgets8[8] = { 100, 250, 500, 750, 1000, 3000, 6000, 12000 };
//const uint64_t CustomAllocator::budgets8[8] = { 50, 100, 150, 200, 400, 800, 1600, 3200 };


const uint64_t CustomAllocator::budgets8[10][8] = { 
  {100, 500, 1000, 2000, 4000, 8000, 16000, 32000 },  // CUSTOM
  {100, 500,  1000, 1500, 3000, 6000, 12000, 24000 }, // CHAMELEON
  {500, 500, 500, 500, 500, 500, 500, 500 },          // CONST1
  {100, 200, 400, 800, 1600, 3200, 6400, 12800},      // EXP
  {500, 1000, 1500, 2000, 8000, 8500, 9000, 10000},   // GAP
  {100, 300, 600, 1000, 1500, 2100, 2800, 3600},      // INCREASING1
  {100, 500, 1100, 1900, 2900, 4100, 5500, 7100},     // INCREASING2
  {500, 1000, 1500, 2000, 2500, 3000, 3500, 4000},    // SIMPLE1
  {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000},    // SIMPLE2
  {500, 2000, 3500, 5000, 6500, 8000, 9500, 11000},   // SIMPLE3
};

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
      return budgets8[custom][queue];
    default:
      throw cRuntimeError("Unsupported number of QoS queues: %i", numQueues);
  }
}


}