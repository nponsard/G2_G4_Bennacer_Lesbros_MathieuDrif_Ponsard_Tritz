#include "line.h"

#include "../tools/CstCodErr.h"
#include "../tools/tools.h"
#include <cmath>

using namespace std;
using namespace nsUtil;

minGL &line::_Edit(minGL &Window) const throw (myexception)
{
    //pour eviter de faire moultes recherches
    pos pMin (remarkablePt.find("posMin")->second);
    pos pMax (remarkablePt.find("posMax")->second);
    if (pMin.abs != pMax.abs)
    {
        pair <float, float> equaPminPmax = computeab(pMin, pMax);
        for (unsigned x (pMin.abs); x <= pMax.abs; ++x) {
            //Window.setPixel (pos (x, equaPminPmax.first * x + equaPminPmax.second), borderColor);
            Window.setPixel (pos (x, (unsigned) ceil(equaPminPmax.first * (float) x + equaPminPmax.second)), borderColor);
        }
    }
    else
    {
        for (unsigned y (pMin.ord); y <= pMax.ord; ++y)
            Window.setPixel (pos (pMin.abs, y), borderColor);
    }
    return Window;
}

line::line(const pos & pos1, const pos & pos2, const RGBcolor &fillCol)
{
    pos tmp = pos::min (pos1, pos2);
    remarkablePt ["posMin"] = tmp;
    remarkablePt ["posMax"] = ((tmp == pos1) ? pos2 : pos1);
    inColor = borderColor = fillCol;
    name = "line";
}

line::line(const baseFig & b) throw (myexception)
{
    if (b.remarkablePt.size() != 2) throw myexception (kNoLine);
    remarkablePt = b.remarkablePt;
    borderColor = b.borderColor;
    inColor = b.inColor;
    name = "triangle";
}


