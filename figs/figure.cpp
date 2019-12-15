#include "figure.h"

#include "line.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"


using namespace std;
using namespace nsUtil;

minGL &figure::_Edit(minGL &Window) const throw (myexception)
{
    for (const auto & fig : vFig)
        Window << *fig;
    return Window;
}

//hop un coup d'intropsection
//mais on ne peut pas faire autrement à cause du profil de la fonction
//void figure::Add(const baseFig &val) throw (myexception)
//{
//    //std::shared_ptr<baseFig> tmp;
//    if (val.getName() == "line")
//    {
//        std::shared_ptr<line> tmp (new line (val));
//        vFig.push_back(tmp);
//    }
//    else if (val.getName() == "triangle")
//    {
//        std::shared_ptr<triangle> tmp (new triangle (val));
//        vFig.push_back(tmp);
//    }
//    else if (val.getName() == "rectangle")
//    {
//        std::shared_ptr<rectangle> tmp (new rectangle (val));
//        vFig.push_back(tmp);
//    }
//    else if (val.getName() == "circle")
//    {
//        std::shared_ptr<circle> tmp (new circle (val));
//        vFig.push_back(tmp);
//    }
//    else throw myexception (kTypeNotFound);
//}


figure figure::operator *(const float &f) const
{
    figure tmp;
    for (unsigned i(0); i < this->vFig.size(); ++i)
    {
        if (vFig[i]->getName() == "circle")
            tmp.Add(circle (*vFig[i]).operator * (f));
        else if (vFig[i]->getName() == "rectangle")
            tmp.Add(rectangle (*vFig[i]).operator * (f));
        else if (vFig[i]->getName() == "triangle")
            tmp.Add(triangle (*vFig[i]).operator * (f));
        else if (vFig[i]->getName() == "line")
            tmp.Add(line (*vFig[i]).operator * (f));
    }
    return tmp;
}

figure figure::operator +(const pos &pos_) const
{
    figure tmp;
    for (unsigned i(0); i < this->vFig.size(); ++i)
    {
        if (vFig[i]->getName() == "circle")
            tmp.Add(circle (*vFig[i]).operator + (pos_));
        else if (vFig[i]->getName() == "rectangle")
            tmp.Add(rectangle (*vFig[i]).operator + (pos_));
        else if (vFig[i]->getName() == "triangle")
            tmp.Add(triangle (*vFig[i]).operator + (pos_));
        else if (vFig[i]->getName() == "line")
            tmp.Add(line (*vFig[i]).operator + (pos_));
    }
    return tmp;
}

