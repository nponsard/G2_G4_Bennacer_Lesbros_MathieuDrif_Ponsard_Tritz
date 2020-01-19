#ifndef CIRCLE_H
#define CIRCLE_H

#include "pixel.h"

class circle
{

public:
    pixel center;
    unsigned radius;
    RGBcolor  borderColor, inColor;
    circle(const pixel & pix, const unsigned & rad, const RGBcolor & borderCol, const RGBcolor & inCol = RGBcolor ());
    circle operator + (const pixel & pix) const;
    circle operator * (const float & reductionRatio) const;
};

#endif // CIRCLE_H
