#include "tools.h"

// Renvoie le coefficient de la droite passant par pt1 et pt2, ET
// pair<coef_directeur, decalage>
std::pair <float, float> computeab (const pos & pt1, const pos & pt2)
{
    //float a = (float (uAbs(pt2.ord, pt1.ord)) / (float (uAbs (pt2.abs, pt1.abs))));
    float a = (float ((int) pt2.ord - (int) pt1.ord)) / (float ((int) pt2.abs - (int) pt1.abs));
    float b = pt2.ord - a * pt2.abs;
    return std::make_pair (a,b);
}//computeab ()
