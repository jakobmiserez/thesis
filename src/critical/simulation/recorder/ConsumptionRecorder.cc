#include "ConsumptionRecorder.h"
#include "ConsumptionManager.h"

namespace critical {

Register_Class(ConsumptionRecorderData);

Register_ResultRecorder("recordConsumption", ConsumptionRecorder);

void ConsumptionRecorder::receiveSignal(cResultFilter *prev, simtime_t_cref t, cObject *obj, cObject *details) {
  ConsumptionRecorderData* data = check_and_cast<ConsumptionRecorderData*>(obj);
  ConsumptionManager::getInstance()->recordConsumption(
    data->getSource(), 
    t, 
    data->getInterfaceId(), 
    data->getAddedConsumption(),
    data->getMaxConsumption()
  );
}

}