#include "FlowRequirementsRecorder.h"

#include <iostream>
#include <fstream>

namespace critical {

Register_ResultRecorder("captureFlow", FlowRequirementsRecorder);

void FlowRequirementsRecorder::finish(cResultFilter *prev) {
  if (flows.size() > 0) {
    std::ofstream out(getOutputFileName());

    if (out.fail()) {
      return;
    }

    out << "source,sink,delay,rate,burst\n";

    for (int i = 0; i < flows.size(); i++) {
      FlowRequirements& req = flows[i];
      out << req.getSource()->getFullPath() << ",";
      out << req.getSink()->getFullPath() << ",";
      out << req.getFlowParameters().delay << ",";
      out << req.getFlowParameters().rate << ",";
      out << req.getFlowParameters().burst << "\n";
    }

    out.close();

  }
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
  const FlowRequirements* req = check_and_cast<FlowRequirements*>(obj);
  flows.push_back(*req);
}

std::string FlowRequirementsRecorder::getOutputFileName() {
  cConfigOption* opt = cConfigOption::find("output-scalar-file");

  //getSimulation()->getActiveEnvir()->getConfigEx()->getActiveRunNumber()

  std::string filename = getSimulation()->getActiveEnvir()->getConfig()->getAsFilename(opt);
  if (getSimulation()->getActiveEnvir()->getConfigEx()->getActiveRunNumber() > 0) {
    //throw cRuntimeError("YES");
  }
  cStringTokenizer tokenizer(filename.c_str(), ".");

  std::string finalName(tokenizer.nextToken());
  finalName += "-flows.csv";

  return finalName;
}


}