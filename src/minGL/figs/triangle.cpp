#include <vector>
#include <algorithm>

#include "triangle.h"
#include "line.h"

#include "../tools/CstCodErr.h"
#include "../tools/tools.h"


using namespace std;
using namespace nsUtil;

minGL &triangle::_Edit(minGL &Window) const throw (myexception)
{
    //pour eviter de faire moultes recherches
    pos pMin (remarkablePt.find("posMin")->second);
    pos pInt (remarkablePt.find("posInt")->second);
    pos pMax (remarkablePt.find("posMax")->second);
    pair <float, float> equaPminPmax = computeab(pMin, pMax);
    pair <float, float> equaPminPint = computeab(pMin, pInt);
    pair <float, float> equaPintPmax = computeab(pInt, pMax);

    //l'inétrieur
    //si pInt est au dessus de la droite pMin -- pMax
    if (pInt.ord > equaPminPmax.first * pInt.abs + equaPminPmax.second)
    {
        //on va de pMin a pInt
        for (unsigned x (pMin.abs + 1); x < pInt.abs; ++x)
            for (unsigned y = equaPminPmax.first * x + equaPminPmax.second + 1;
                 y < equaPminPint.first * x + equaPminPint.second; ++y)
                Window.setPixel(pos (x, y), inColor);

        //on va de pInt a pMax
        for (unsigned x (pInt.abs); x < pMax.abs; ++x)
            for (unsigned y = equaPminPmax.first * x + equaPminPmax.second + 1;
                 y < equaPintPmax.first * x + equaPintPmax.second; ++y)
                Window.setPixel(pos (x, y), inColor);
    }
    else
    {
        //on va de pMin a pInt
        for (unsigned x (pMin.abs + 1); x < pInt.abs; ++x)
            for (unsigned y = equaPminPint.first * x + equaPminPint.second +1;
                 y < equaPminPmax.first * x + equaPminPmax.second; ++y)
                Window.setPixel(pos (x, y), inColor);

        //on va de pInt a pMax
        for (unsigned x (pInt.abs + (pInt.abs == pMin.abs ? 1 : 0)); x < pMax.abs; ++x)
            for (unsigned y = equaPintPmax.first * x + equaPintPmax.second + 1;
                 y < equaPminPmax.first * x + equaPminPmax.second; ++y)
                Window.setPixel(pos (x, y), inColor);
    }
    //le pourtour
    Window << line (pMin, pMax, borderColor);
    Window << line (pMin, pInt, borderColor);
    Window << line (pInt, pMax, borderColor);

    return Window;
}

triangle::triangle(const pos &pos1, const pos &pos2, const pos &pos3, const RGBcolor &borderCol_, const RGBcolor &fillCol_)

{
    vector<pos> Vpos {pos1, pos2, pos3} ;

    sort (Vpos.begin(), Vpos.end (), pos::minf);
//    sort (Vpos.begin(), Vpos.end(), [](pos a, pos b) {
//        return a.abs < b.abs;
//    });
//    if (Vpos[0].abs == Vpos[1].abs)
//    {
//        //est-ce qu'on a une ligne?
//        if (Vpos[0].abs == Vpos[2].abs)
//            //on trie selon les ordonnées
//            sort (Vpos.begin(), Vpos.end(), [](pos a, pos b) {
//                return a.ord < b.ord;
//            });
//        else if (Vpos[0].ord > Vpos[1].ord)
//            swap (Vpos[0], Vpos[1]);
//    }

    remarkablePt ["posMin"] = Vpos[0];
    remarkablePt ["posInt"] = Vpos[1];
    remarkablePt ["posMax"] = Vpos[2];
    borderColor = borderCol_;
    inColor = fillCol_;
    name = "triangle";
}

triangle::triangle(const baseFig & b) throw (myexception)
{
    if (b.remarkablePt.size() != 3) throw myexception (kNoTriangle);
    remarkablePt = b.remarkablePt;
    borderColor = b.borderColor;
    inColor = b.inColor;
    name = "triangle";
}
