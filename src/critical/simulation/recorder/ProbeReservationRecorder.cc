#include "ProbeReservationRecorder.h"

namespace critical {

Register_ResultRecorder("recordProbeReservation", ProbeReservationRecorder);

ProbeReservationManager* ProbeReservationManager::instance = nullptr;

void ProbeReservationManager::init() {
    getEnvir()->addLifecycleListener(this);
    std::string fname = getOutputFileName();
    out = std::ofstream(fname);

    if (out.fail()) {
        std::string msg;
        msg += "Unable to open probe reservations output file name: ";
        msg += fname;
        throw cRuntimeError(msg.c_str());    
    }
    out << "flow,maxProbeReservations\n";
}

void ProbeReservationManager::lifecycleEvent(SimulationLifecycleEventType eventType, cObject *details) {
    if (eventType == SimulationLifecycleEventType::LF_ON_RUN_END) {
        for (size_t i = 0; i < map.size(); i++) {
            const auto entry = map.at(i);
            out << entry->flow.toIdString() << "," << entry->data.maxReservations << "\n";
        }
        map.clear();
    
        out.close();
        delete this;
        instance = nullptr;
    }
}

void ProbeReservationManager::recordProbeReservation(const ProbeReservationData& data) {
    auto entry = map.lookupFlow(data.getFlowId());
    if (entry == nullptr) {
        ASSERT(data.getDelta() == 1);
        ProbeReservationManager::Data reservation_data;
        reservation_data.maxReservations = 1;
        reservation_data.currentReservations = 1;
        map.insertFlow(data.getFlowId(), reservation_data);
        return;
    }

    if (data.getDelta() < 0 && entry->data.currentReservations < -data.getDelta()) {
        entry->data.currentReservations = 0;
    }
    else {
        entry->data.currentReservations += data.getDelta();
    }

    if (entry->data.currentReservations > entry->data.maxReservations) {
        entry->data.maxReservations = entry->data.currentReservations;
    }
}

std::string ProbeReservationManager::getOutputFileName() {
  cConfigOption* opt = cConfigOption::find("output-scalar-file");

  std::string filename = getSimulation()->getActiveEnvir()->getConfig()->getAsFilename(opt);
  cStringTokenizer tokenizer(filename.c_str(), ".");

  std::string finalName(tokenizer.nextToken());
  finalName += "-probeReservations.csv";

  return finalName;
}

void ProbeReservationRecorder::receiveSignal(cResultFilter *prev, simtime_t_cref t, cObject *obj, cObject *details) {
  ProbeReservationData* data = check_and_cast<ProbeReservationData*>(obj);
  ProbeReservationManager::getInstance()->recordProbeReservation(*data);
}

}

