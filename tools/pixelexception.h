#ifndef PIXELEXCEPTION_H
#define PIXELEXCEPTION_H

#include <exception>
#include "../graph/pos.h"
#include "../graph/rgbcolor.h"

class PixelException : public std::exception
{
public:
    PixelException(const pos &pixelPosition, const RGBcolor &color, const std::string &problem);
    const char* what() const noexcept;

private:
    pos pixelPosition;
    RGBcolor pixelColor;
    std::string problem;
};

#endif // PIXELEXCEPTION_H
