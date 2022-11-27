#include "ConsumptionChecker.h"

#include <omnetpp.h>

using namespace omnetpp;

namespace critical {

ConsumptionChecker::ConsumptionChecker() 
: total(0), consumption(0) {

}
  
ConsumptionChecker::~ConsumptionChecker() {

}

void ConsumptionChecker::init(double total, double threshPercentage) {
  EV_INFO << "(CONSUMPTION CHECKER) Initalizing " << threshPercentage << "\n";
  this->total = total;
  this->step = total * threshPercentage;
  this->previousThresh = 0;
  this->nextThresh = step;
  EV_INFO << "(CONSUMPTION CHECKER) Step: " << step << "\n";
}

bool ConsumptionChecker::addConsumption(double consumption) {
  double newConsumption = this->consumption + consumption;
  if (newConsumption > total) {
    throw cRuntimeError("Consumption cannot go higher than total consumption: %f vs %f", newConsumption, total);
  }
  this->consumption = newConsumption;
  logConsumption();
  if (newConsumption >= nextThresh) {
    nextThresh += step;
    while (newConsumption >= nextThresh) {
      nextThresh += step;
    }
    previousThresh = nextThresh - step;
    return true;
  }
  return false;
}

bool ConsumptionChecker::removeConsumption(double consumption) {
  double newConsumption = this->consumption - consumption;
  if (newConsumption < 0) {
    throw cRuntimeError("Consumption cannot go lower than zero");
  }
  this->consumption = newConsumption;
  logConsumption();
  if (newConsumption < previousThresh) {
    previousThresh -= step;
    while (newConsumption < previousThresh) {
      previousThresh -= step;
    }
    nextThresh = previousThresh + step;
    return true;
  }
  return false;
}

void ConsumptionChecker::logConsumption() {
  EV_INFO << "(CONSUMPTION CHECKER) Consumption at " << (consumption / total) << " (" << consumption << ")\n";
  EV_INFO << "(CONSUMPTION CHECKER) Next threshold at " << (nextThresh / total) << " (" << nextThresh << ")\n";
}


}