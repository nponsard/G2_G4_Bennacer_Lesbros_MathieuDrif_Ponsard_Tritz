#ifndef MAINSPACEINVADERS_H
#define MAINSPACEINVADERS_H

#include "minGL/graph/mingl.h"
#include "utils/spaceinvaders.h"

void mainSI(minGL &window);
void process(spaceInvaders &SI, const unsigned &height, const unsigned &width, bool &iLoose, bool &iWin);

#endif // MAINSPACEINVADERS_H
