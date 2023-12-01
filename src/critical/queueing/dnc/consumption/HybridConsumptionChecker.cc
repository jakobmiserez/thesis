#include "HybridConsumptionChecker.h"

#include <math.h>
#include <omnetpp.h>

namespace critical {

HybridConsumptionChecker::HybridConsumptionChecker(): total(0), consumption(0), lastUpdate(0) {

}

HybridConsumptionChecker::~HybridConsumptionChecker() {

}

void HybridConsumptionChecker::init(double total, double threshPercentage) {
    this->total = total;
    this->thresh = total * threshPercentage;
}

bool HybridConsumptionChecker::addConsumption(double consumptionToAdd) {
    consumption += consumptionToAdd;
    if (abs(consumption - lastUpdate) > thresh) {
        lastUpdate = consumption;
        return true;
    }
    return false;
}

bool HybridConsumptionChecker::removeConsumption(double consumptionToAdd) {
    return addConsumption(-consumptionToAdd);
}

void HybridConsumptionChecker::onTimeBasedUpdate() {
    lastUpdate = consumption;
}


}