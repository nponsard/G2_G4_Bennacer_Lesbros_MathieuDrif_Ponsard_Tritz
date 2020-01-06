#include "minglstring.h"

minglString::minglString(const pixel & pi, const std::string & str) : pix (pi), data (str)
{

}

minglString minglString::operator +(const pixel &pix_) const
{
    return minglString (pix + pix_, data);
}

minglString minglString::operator *(const float &reductionRatio) const
{
    return minglString (pix * reductionRatio, data);
}

minglString  operator +(const pixel &pix, const std::string &str)
{
    return minglString (pix, str);
}
