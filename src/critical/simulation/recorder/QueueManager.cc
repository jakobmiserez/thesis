#include "QueueManager.h"

#include <fstream>

namespace critical {

QueueManager* QueueManager::instance = nullptr;

void QueueManager::init() {
  getSimulation()->getActiveEnvir()->addLifecycleListener(this);

  out = std::ofstream(getOutputFileName());
  if (out.fail()) {
    throw cRuntimeError("Unable to open consumption output file name");    
  }
  out << "source,interfaceId,queue,time,hd,mhd,vd,mvd\n";
}

void QueueManager::lifecycleEvent(SimulationLifecycleEventType eventType, cObject *details) {
  if (eventType == SimulationLifecycleEventType::LF_ON_RUN_END) {
    out.close();
    delete this;
    instance = nullptr;
  }
}

void QueueManager::recordConsumption(simtime_t t, QueueRecorderData* data) {
  out << data->getSource()->getFullPath() << ",";
  out << data->getInterfaceId() << ",";
  out << data->getQueue() << ",";
  out << t << ",";
  out << data->getHorizontalDeviation() << ",";
  out << data->getMaxHorizontalDeviation() << ",";
  out << data->getVerticalDeviation() << ",";
  out << data->getMaxVerticalDeviation() << "\n";
}

std::string QueueManager::getOutputFileName() {
  cConfigOption* opt = cConfigOption::find("output-scalar-file");

  std::string filename = getSimulation()->getActiveEnvir()->getConfig()->getAsFilename(opt);
  cStringTokenizer tokenizer(filename.c_str(), ".");

  std::string finalName(tokenizer.nextToken());
  finalName +=  "-queues.csv";

  return finalName;
}

}