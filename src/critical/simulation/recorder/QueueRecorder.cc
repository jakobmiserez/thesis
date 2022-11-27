#include "QueueRecorder.h"
#include "QueueManager.h"

namespace critical {

Register_Class(QueueRecorderData);
Register_ResultRecorder("recordQueueState", QueueRecorder);

void QueueRecorder::receiveSignal(cResultFilter *prev, simtime_t_cref t, cObject *obj, cObject *details) {
  QueueRecorderData* data = check_and_cast<QueueRecorderData*>(obj);
  QueueManager::getInstance()->recordConsumption(t, data);
}

}