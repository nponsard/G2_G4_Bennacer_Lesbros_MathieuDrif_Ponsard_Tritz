#ifndef MINGLSTRING_H
#define MINGLSTRING_H

#include <string>

#include "pixel.h"


class minglString
{

public:
    pixel pix;
    std::string data;


    minglString(const pixel &, const std::string &);
    minglString operator + (const pixel & pix_) const;
    minglString operator * (const float & reductionRatio) const;

};

minglString  operator +(const pixel &pix, const std::string &str);


#endif // MINGLSTRING_H
