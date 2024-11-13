#include "CriticalAppGenerator.h"

namespace critical {

const Application CriticalAppGenerator::database(kb(300), kb(550), 100, 400, 80,  120);
const Application CriticalAppGenerator::scada(kb(150), kb(550), 100, 400, 150, 200);
const Application CriticalAppGenerator::production(kb(100), kb(500), 100, 400, 10, 20);
const Application CriticalAppGenerator::control(kb(1), kb(100), 80, 120, 10,  20);
const Application CriticalAppGenerator::video(mb(4), mb(16), 1400, 1800, 50, 200);
const Application CriticalAppGenerator::datamining(mb(80), mb(200), 1000, 3000, 50, 100);
const Application CriticalAppGenerator::other(kb(150), mb(16), 100, 3000, 10, 200);

const std::vector<const Application*> CriticalAppGenerator::apps =  {
  &database,
  &scada,
  &production,
  &control,
  &video,
  //&datamining,
  //&other
};

const std::array<std::array<uint8_t, 5>, CriticalAppGenerator::APP_DISTRIBUTION_COUNT> CriticalAppGenerator::distributionWeights = {{
  { 20, 20, 20, 20, 20 }, // RANDOM
  { 15, 15, 15, 15, 40 }, // VIDEO_40
  { 10, 10, 10, 10, 60 }, // VIDEO_60
  { 5, 5, 5, 5, 80 },     // VIDEO_80
  { 0, 0, 0, 0, 100},     // VIDEO_100
  { 40, 15, 15, 15, 15 }, // DB_40
  { 60, 10, 10, 10, 10 }, // DB_60
  { 80, 5, 5, 5, 5 },     // DB_80
  { 100, 0, 0, 0, 0},     // DB_100
  { 15, 15, 40, 15, 15 }, // PROD_40
  { 10, 10, 60, 10, 10 }, // PROD_60
  { 5, 5, 80, 5, 5 },     // PROD_80
  { 0, 0, 100, 0, 0},     // PROD_100
}};

CriticalAppGenerator::CriticalAppGenerator(): histogram("appDistributionHistogram") {
  histogram.setRange(0, apps.size());
  histogram.setNumBinsHint(apps.size());
  histogram.setMode(cHistogram::MODE_INTEGERS);
}

void CriticalAppGenerator::setupHistogram() {
  const auto& appWeight = distributionWeights[appDistribution];

  for (size_t i = 0; i < appWeight.size(); i++) {
    for (uint8_t j = 0; j < appWeight[i]; j++) {
      histogram.collect(i);
    }
    //histogram.collectWeighted(i, appWeight[i]);
  }
}

FlowParameters CriticalAppGenerator::generateParameters(cRNG* rng) {

  histogram.setRNG(rng);
  unsigned long category = histogram.draw();

  //unsigned long category = rng->intRand(apps.size());
  return apps[category]->generateParams(rng);
};   

}