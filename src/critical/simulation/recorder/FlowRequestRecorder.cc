#include "FlowRequestRecorder.h"
#include "FlowRequestResponseManager.h"
#include "FlowRecorderData.h"

namespace critical {

Register_ResultRecorder("recordFlowRequest", FlowRequestRecorder);

void FlowRequestRecorder::receiveSignal(cResultFilter *prev, simtime_t_cref t, cObject *obj, cObject *details) {
  FlowRequestData* data = check_and_cast<FlowRequestData*>(obj);
  FlowRequestResponseManager::getInstance()->recordFlowRequest(data->getSource(), t);
}

}