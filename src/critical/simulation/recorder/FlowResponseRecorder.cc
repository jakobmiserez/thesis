#include "FlowResponseRecorder.h"
#include "FlowRecorderData.h"
#include "FlowRequestResponseManager.h"

namespace critical {

Register_ResultRecorder("recordFlowResponse", FlowResponseRecorder)

void FlowResponseRecorder::receiveSignal(cResultFilter *prev, simtime_t_cref t, cObject *obj, cObject *details) {
  FlowResponseData* data = check_and_cast<FlowResponseData*>(obj);
  FlowRequestResponseManager::getInstance()->recordFlowResponse(data, t);
}

}

