#include "rgbcolor.h"

//using namespace nsUtil;

//RGBcolor::RGBcolor(const GLubyte &R, const GLubyte &G, const GLubyte &B) : Red (R), Green (G), Blue (B)
//{

//}

std::ostream &RGBcolor::_Edit(std::ostream &os) const
{
    os << "Rouge  : " << int(Red) << " Bleu : " << int(Blue) << " Vert : " << int(Green);
    return os;
}
