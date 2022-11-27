#include "FlowRerouteRecorder.h"
#include "FlowRecorderData.h"
#include "FlowRequestResponseManager.h"

namespace critical {

Register_ResultRecorder("recordFlowReroute", FlowRerouteRecorder)

void FlowRerouteRecorder::receiveSignal(cResultFilter *prev, simtime_t_cref t, cObject *obj, cObject *details) {
  FlowRerouteData* data = check_and_cast<FlowRerouteData*>(obj);
  FlowRequestResponseManager::getInstance()->recordFlowReroute(data->getSource(), t, data->isAccepted());
}

}

