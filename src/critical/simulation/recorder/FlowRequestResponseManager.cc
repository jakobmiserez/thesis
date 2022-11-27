#include "FlowRequestResponseManager.h"

#include <fstream>

namespace critical {

FlowRequestResponseManager* FlowRequestResponseManager::instance = nullptr;

void FlowRequestResponseManager::lifecycleEvent(SimulationLifecycleEventType eventType, cObject *details) {
  if (eventType == SimulationLifecycleEventType::LF_ON_RUN_END) {
    
    if (list.size() > 0) {
      std::ofstream out(fname);

      if (out.fail()) {
        delete this;
        instance = nullptr;
        return;
      }

      out << "source,requestTime,responseTime,accepted,rerouteTime,rerouteAccepted\n";

      for (const auto& data: list) {
        out << data.source << ",";
        out << data.requestTime << ",";
        out << data.responseTime << ",";
        out << data.accepted << ",";
        out << data.rerouteTime << ",";
        out << data.rerouteAccepted << "\n";
      }

      out.close();
    }
    delete this;
    instance = nullptr;
  }
}

void FlowRequestResponseManager::recordFlowRequest(cModule* source, simtime_t t) {
  Data data;
  data.requestTime = t;
  data.source = source->getFullPath();

  list.push_back(data);
  map[source->getId()] = list.size() - 1;
}

void FlowRequestResponseManager::recordFlowResponse(cModule* source, simtime_t t, bool accepted) {
  if (map.find(source->getId()) == map.end()) {
    return;
  }
  int id = map.at(source->getId());
  
  Data& data = list[id];
  data.accepted = accepted;
  data.responseTime = t;
}

void FlowRequestResponseManager::recordFlowReroute(cModule* source, simtime_t t, bool accepted) {
  if (map.find(source->getId()) == map.end()) {
    return;
  }
  int id = map.at(source->getId());

  Data& data = list[id];
  data.rerouteTime = t;
  data.rerouteAccepted = accepted;
}

std::string FlowRequestResponseManager::getOutputFileName() {
  cConfigOption* opt = cConfigOption::find("output-scalar-file");

  std::string filename = getSimulation()->getActiveEnvir()->getConfig()->getAsFilename(opt);
  cStringTokenizer tokenizer(filename.c_str(), ".");

  std::string finalName(tokenizer.nextToken());
  finalName += "-flowtimes.csv";

  return finalName;
}

}