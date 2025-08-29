#include "FlowSignalingRecorder.h"
#include "FlowRequestResponseManager.h"

namespace critical {

Register_ResultRecorder("recordFlowSignaling", FlowSignalingRecorder);

void FlowSignalingRecorder::receiveSignal(cResultFilter *prev, simtime_t_cref t, cObject *obj, cObject *details) {
    FlowSignalingData* data = check_and_cast<FlowSignalingData*>(obj);
    FlowRequestResponseManager::getInstance()->recordFlowSignaling(data, t);
}

}