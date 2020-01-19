#include "circle.h"


circle::circle(const pixel &pix, const unsigned &rad, const RGBcolor &borderCol, const RGBcolor &inCol) :
    center (pix), radius (rad), borderColor (borderCol), inColor (inCol)
{

}

circle circle::operator +(const pixel &pix) const
{
    return circle (center + pix, radius, borderColor, inColor);
}

circle circle::operator *(const float &reductionRatio) const
{
    return circle (center * reductionRatio, radius * reductionRatio, borderColor, inColor);
}
