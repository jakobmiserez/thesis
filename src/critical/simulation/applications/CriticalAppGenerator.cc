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

FlowParameters CriticalAppGenerator::generateParameters(cRNG* rng) {
  unsigned long category = rng->intRand(apps.size());
  return apps[category]->generateParams(rng);
};   

}