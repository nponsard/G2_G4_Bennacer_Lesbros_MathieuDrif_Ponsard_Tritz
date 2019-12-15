#include "pixelexception.h"

#include <string>
#include <sstream>

using namespace std;

PixelException::PixelException(const pos &pixelPosition, const RGBcolor &color, const std::string &problem)
    : pixelPosition(pixelPosition), pixelColor(color), problem(problem)
{

}

const char* PixelException::what() const noexcept {

    ostringstream sstr;

    sstr << "Pixel error: ";
    sstr << "(" << pixelPosition.abs << "," << pixelPosition.ord << ") ";
    sstr << "[rgb " << (unsigned) pixelColor.Red << ", " << (unsigned) pixelColor.Green << ", " << (unsigned) pixelColor.Blue << "]: ";
    sstr << problem;

    // TODO: Change
    //cout << sstr.str().c_str() << endl;

    return sstr.str().c_str();
}
