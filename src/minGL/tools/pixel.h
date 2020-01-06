#ifndef PIXEL_H
#define PIXEL_H

#include <string>

#include "../graph/rgbcolor.h"
#include "tools.h"

class pixel
{
public:
    unsigned abs;
    unsigned ord;
    RGBcolor color;

    pixel (const unsigned & Abscisse = 0, const unsigned & Ordonnee = 0, const RGBcolor & coul = RGBcolor ());
    pixel operator + (const pixel & pix) const {return pixel (abs + pix.abs, ord + pix.ord, color);}
    bool operator == (const pixel & pix) const {return pix.abs == abs && pix.ord == ord;}
    pixel operator * (const float & reductionRation) const {return pixel (abs*reductionRation, ord*reductionRation);}
    pixel operator *(const pixel & pix) const {return pixel (abs*pix.abs, ord*pix.ord);}
};

#endif // PIXEL_H
