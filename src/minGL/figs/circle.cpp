#include <cmath>

#include "circle.h"

#include "../tools/CstCodErr.h"

using namespace std;
using namespace nsUtil;

minGL &circle::_Edit(minGL &Window) const throw (myexception)
{
    //pour eviter de faire moultes recherches
    pos center (remarkablePt.find("ptCent")->second);
    unsigned radius (remarkablePt.find("radius")->second.ord);

    //le pourtour
    double j, inc = asin((double)1/radius);
    for (j=0; j<360; j+=inc) {
      Window.setPixel(pos (center.abs+cos(j)*radius, center.ord+sin(j)*radius), borderColor);
    }

    //l'intérieur
    for (unsigned i (0); i < radius - 1; ++i) {
        for (unsigned j (0); j < sqrt(radius*radius - i*i) -1; ++j) {
            Window.setPixel (pos (center.abs+j, center.ord+i), inColor);
            Window.setPixel (pos (center.abs-j, center.ord+i), inColor);
            Window.setPixel (pos (center.abs+j, center.ord-i), inColor);
            Window.setPixel (pos (center.abs-j, center.ord-i), inColor);
        }
    }

    return Window;
}

circle::circle(const pos &pos_, const unsigned &rad, const RGBcolor &borderCol, const RGBcolor &inCol)
{
    remarkablePt["ptCent"] = pos_;
    remarkablePt["radius"] = pos (0, rad);
    borderColor = borderCol;
    inColor = inCol;
    name = "circle";
}

circle::circle(const baseFig & b) throw (myexception)
{
    if (b.remarkablePt.size() != 2) throw myexception (kNoTriangle);
    remarkablePt = b.remarkablePt;
    borderColor = b.borderColor;
    inColor = b.inColor;
    name = "circle";
}

//circle circle::operator *(const float &f) const
//{
//    circle tmp (*this);
//    tmp.remarkablePt.find("radius")->second.ord = tmp.remarkablePt.find("ptCent")->second.ord * f;
//    return tmp;
//}

circle circle::operator +(const pos &pos_) const
{
    circle tmp (*this);
    tmp.remarkablePt.find("ptCent")->second = tmp.remarkablePt.find("ptCent")->second + pos_;
    return tmp;
}
