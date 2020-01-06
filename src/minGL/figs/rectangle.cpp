#include "rectangle.h"
#include "triangle.h"
#include "line.h"

#include "../tools/CstCodErr.h"

using namespace std;
using namespace nsUtil;

minGL &rectangle::_Edit(minGL &Window) const throw (myexception)
{
    //pour eviter de faire moultes recherches
    pos botLeft (remarkablePt.find("botLeft")->second);
    pos topLeft (remarkablePt.find("topLeft")->second);
    pos botRight (remarkablePt.find("botRight")->second);
    pos topRight (remarkablePt.find("topRight")->second);

    //le pourtour
    Window << line (botLeft, topLeft, borderColor);
    Window << line (topLeft, topRight, borderColor);
    Window << line (topRight, botRight, borderColor);
    Window << line (botRight, botLeft, borderColor);

    //l'interieur
    for (unsigned x (botLeft.abs + 1); x < topRight.abs; ++x)
        for (unsigned y (botLeft.ord +1); y < topRight.ord; ++y)
            Window.setPixel (pos (x, y), inColor);

    //une version avec des triangles (fonctionne?)
   /* Window << triangle (botLeft, topLeft, topRight, borderColor, inColor);
    Window << triangle (botLeft, botRight, topRight, borderColor, inColor);
    Window << line (botLeft, topRight, inColor);
*/
    return Window;
}

rectangle::rectangle(const pos &pos1, const pos &pos2, const RGBcolor &borderCol, const RGBcolor &inCol)
{
    remarkablePt ["botLeft"]  = pos (min (pos1.abs, pos2.abs), min (pos1.ord, pos2.ord));
    remarkablePt ["topLeft"]  = pos (min (pos1.abs, pos2.abs), max (pos1.ord, pos2.ord));
    remarkablePt ["botRight"] = pos (max (pos1.abs, pos2.abs), min (pos1.ord, pos2.ord));
    remarkablePt ["topRight"] = pos (max (pos1.abs, pos2.abs), max (pos1.ord, pos2.ord));
    borderColor = borderCol;
    inColor = inCol;
    name = "rectangle";
}

rectangle::rectangle(const pos &pos_, const unsigned &width, const unsigned &height, const RGBcolor &borderCol, const RGBcolor &inCol)
{
    remarkablePt ["botLeft"]  = pos_;
    remarkablePt ["topLeft"]  = pos_ + pos (0, height);
    remarkablePt ["botRight"] = pos_ + pos (width, 0);
    remarkablePt ["topRight"] = pos_ + pos (width, height);
    borderColor = borderCol;
    inColor = inCol;
    name = "rectangle";
}

rectangle::rectangle(const baseFig & b) throw (myexception)
{
    if (b.remarkablePt.size() != 4) throw myexception (kNoRectangle);
    remarkablePt = b.remarkablePt;
    borderColor = b.borderColor;
    inColor = b.inColor;
    name = "rectangle";
}
