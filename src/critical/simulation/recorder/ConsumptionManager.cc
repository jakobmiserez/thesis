#include "ConsumptionManager.h"

#include <fstream>

namespace critical {

ConsumptionManager* ConsumptionManager::instance = nullptr;

void ConsumptionManager::init() {
  getSimulation()->getActiveEnvir()->addLifecycleListener(this);

  std::string outputFile = getOutputFileName();
  out = std::ofstream(outputFile);
  if (out.fail()) {
    std::string msg;
    msg += "Unable to open consumption output file name: ";
    msg += outputFile;
    throw cRuntimeError(msg.c_str());    
  }
  out << "source,interfaceId,time,addedConsumption,maxConsumption\n";
}

void ConsumptionManager::lifecycleEvent(SimulationLifecycleEventType eventType, cObject *details) {
  if (eventType == SimulationLifecycleEventType::LF_ON_RUN_END) {
    out.close();
    delete this;
    instance = nullptr;
  }
}

void ConsumptionManager::recordConsumption(
  cModule* source, simtime_t t, int interfaceId, 
  double addedConsumption, double maxConsumption
) {
  out << source->getFullPath() << ",";
  out << interfaceId << ",";
  out << t << ",";
  out << addedConsumption << ",";
  out << maxConsumption << "\n";
}

std::string ConsumptionManager::getOutputFileName() {
  cConfigOption* opt = cConfigOption::find("output-scalar-file");

  std::string filename = getSimulation()->getActiveEnvir()->getConfig()->getAsFilename(opt);
  cStringTokenizer tokenizer(filename.c_str(), ".");

  std::string finalName(tokenizer.nextToken());
  finalName +=  "-consumption.csv";

  return finalName;
}

}