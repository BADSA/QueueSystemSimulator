#include "macros.h"

#ifndef QUEUESYSTEMSIMULATOR_PROB_H
#define QUEUESYSTEMSIMULATOR_PROB_H

double media(vf numbers);
vf getObserved(msi numbers);
vf getObserved2(std::vector<ppii> frecuencies);
vf foLessFe(vf observed,vf expected);
vf fAcum(vf v);
std::vector<pii> genRanges(int lower,int upper,float rngAmount);

#endif //QUEUESYSTEMSIMULATOR_PROB_H
