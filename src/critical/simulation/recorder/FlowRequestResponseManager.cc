#include "FlowRequestResponseManager.h"

#include <fstream>

namespace critical {

FlowRequestResponseManager* FlowRequestResponseManager::instance = nullptr;

void FlowRequestResponseManager::init() {
  getEnvir()->addLifecycleListener(this);
  std::string fname = getOutputFileName();
  std::string rname = getReroutesOutputFileName();

  out = std::ofstream(fname);
  outReroutes = std::ofstream(rname);

  if (out.fail() || outReroutes.fail()) {
    std::string msg;
    msg += "Unable to open consumption output file name: ";
    msg += fname;
    msg += "/";
    msg += rname;
    throw cRuntimeError(msg.c_str());    
  }
  out << "source,id,requestTime,responseTime,signalingTime,accepted\n";

  outReroutes << "source,rerouteTime,rerouteAccepted\n";
}

void FlowRequestResponseManager::lifecycleEvent(SimulationLifecycleEventType eventType, cObject *details) {
  if (eventType == SimulationLifecycleEventType::LF_ON_RUN_END) {
    for (const auto& [id, data]: map) {
      out << data->source << ",";
      out << data->requestTime << ",";
      out << data->responseTime << ",";
      out << data->signalingTime << ",";
      out << data->accepted << "\n";
    }
    map.clear();
    
    out.close();
    outReroutes.close();
    delete this;
    instance = nullptr;
  }
}

void FlowRequestResponseManager::recordFlowRequest(FlowRequestData* reqData, simtime_t t) {
  Data* data = new Data();
  data->requestTime = t;
  data->source = reqData->getSource()->getFullPath();
  data->id = reqData->getFlowId();

  map[reqData->getFlowId()] = data;
}

void FlowRequestResponseManager::recordFlowResponse(FlowResponseData* respData, simtime_t t) {
  Data* data = map.at(respData->getId());
  data->responseTime = t;
  data->accepted = respData->isAccepted();

  out << data->source << ",";
  out << data->requestTime << ",";
  out << data->responseTime << ",";
  out << data->signalingTime << ",";
  out << data->accepted << "\n";

  map.erase(respData->getId());
  delete data;
}

void FlowRequestResponseManager::recordFlowReroute(cModule* source, simtime_t t, bool accepted) {
  outReroutes << source->getFullPath() << ",";
  out << t << ",";
  out << accepted << "\n";
}

void FlowRequestResponseManager::recordFlowSignaling(FlowSignalingData* sigData, simtime_t t) {
  Data* data = map.at(sigData->getId());

  // Only record the first signaling time
  if (data->signalingTime == -1)
    data->signalingTime = t;
}

std::string FlowRequestResponseManager::getOutputFileName() {
  cConfigOption* opt = cConfigOption::find("output-scalar-file");

  std::string filename = getSimulation()->getActiveEnvir()->getConfig()->getAsFilename(opt);
  cStringTokenizer tokenizer(filename.c_str(), ".");

  std::string finalName(tokenizer.nextToken());
  finalName += "-flowtimes.csv";

  return finalName;
}

std::string FlowRequestResponseManager::getReroutesOutputFileName() {
  cConfigOption* opt = cConfigOption::find("output-scalar-file");

  std::string filename = getSimulation()->getActiveEnvir()->getConfig()->getAsFilename(opt);
  cStringTokenizer tokenizer(filename.c_str(), ".");

  std::string finalName(tokenizer.nextToken());
  finalName += "-reroutes.csv";

  return finalName;
}

}