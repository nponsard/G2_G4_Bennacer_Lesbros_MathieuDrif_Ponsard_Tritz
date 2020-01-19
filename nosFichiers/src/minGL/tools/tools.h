#ifndef TOOLS_H
#define TOOLS_H

#include <algorithm> //min, max
#include "../graph/pos.h"

//on calcule les coef a et b de la droite aX + b = Y passant par les 2 pts pt1 et pt2
std::pair <float, float> computeab (const pos & pt1, const pos & pt2);


#endif // TOOLS_H
