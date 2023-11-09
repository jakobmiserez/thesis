#include "FlowRequirementsRecorder.h"

#include <iostream>
#include <fstream>

namespace critical {

Register_ResultRecorder("captureFlow", FlowRequirementsRecorder);

void FlowRequirementsRecorder::finish(cResultFilter *prev) {
  out.close();
  isInit = false;
}

void FlowRequirementsRecorder::init() {
  std::string fname = getOutputFileName();
  out = std::ofstream(fname);

  if (out.fail()) {
    std::string f = "Failed to open consumption file";
    f += fname;
    throw cRuntimeError(f.c_str());
  }

  out << "source,sink,delay,rate,burst\n";
  isInit = true;
}

void FlowRequirementsRecorder::receiveSignal(cResultFilter *prev, simtime_t_cref t, bool b, cObject *details) {
  
}

void FlowRequirementsRecorder::receiveSignal(cResultFilter *prev, simtime_t_cref t, long l, cObject *details) {

}

void FlowRequirementsRecorder::receiveSignal(cResultFilter *prev, simtime_t_cref t, unsigned long l, cObject *details) {

}

void FlowRequirementsRecorder::receiveSignal(cResultFilter *prev, simtime_t_cref t, double d, cObject *details) {

}

void FlowRequirementsRecorder::receiveSignal(cResultFilter *prev, simtime_t_cref t, const SimTime& v, cObject *details) {

}

void FlowRequirementsRecorder::receiveSignal(cResultFilter *prev, simtime_t_cref t, const char *s, cObject *details) {

}

void FlowRequirementsRecorder::receiveSignal(cResultFilter *prev, simtime_t_cref t, cObject *obj, cObject *details) {
  if (!isInit) {
    init();
  }
  
  FlowRequirements* req = check_and_cast<FlowRequirements*>(obj);
  out << req->getSource()->getFullPath() << ",";
  out << req->getSink()->getFullPath() << ",";
  out << req->getFlowParameters().delay << ",";
  out << req->getFlowParameters().rate << ",";
  out << req->getFlowParameters().burst << "\n";
}

std::string FlowRequirementsRecorder::getOutputFileName() {
  cConfigOption* opt = cConfigOption::find("output-scalar-file");

  std::string filename = getSimulation()->getActiveEnvir()->getConfig()->getAsFilename(opt);
  cStringTokenizer tokenizer(filename.c_str(), ".");

  std::string finalName(tokenizer.nextToken());
  finalName += "-flows.csv";

  return finalName;
}


}