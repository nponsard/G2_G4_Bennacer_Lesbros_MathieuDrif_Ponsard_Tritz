#include <iostream>

#include "basefig.h"

using namespace std;

baseFig::baseFig()
{

}

//baseFig::baseFig(const baseFig & B) : remarkablePt (B.remarkablePt)
//{

//}

baseFig::baseFig(const std::map<string, pos> & pt, const RGBcolor & bdCol, const RGBcolor & inCol) :
    remarkablePt (pt), borderColor (bdCol), inColor (inCol), name (string ())
{

}

baseFig baseFig::operator +(const pos &pos_) const
{
    map <string, pos> tmp = this->remarkablePt;
    for (auto & pt : tmp)
        pt.second = pt.second + pos_;
    return baseFig (tmp, borderColor, inColor);
}

baseFig baseFig::operator *(const float &f) const
{
    map <string, pos> tmp = this->remarkablePt;
    for (auto & pt : tmp)
        pt.second = pt.second * f;
    return baseFig (tmp, borderColor, inColor);
}

string baseFig::getName() const
{
    return name;
}

baseFig operator *(const float &f, const baseFig & B)
{
    return B * f;
}

baseFig operator +(const pos & pos_, const baseFig & B)
{
    return B + pos_;
}

//std::ostream &baseFig::_Edit(std::ostream &os) const
//{
//    for (const auto & att : remarkablePt)
//        os << "Clé : " << att.first << "  "
//           << "Valeur : (" << att.second.abs << ',' << att.second.ord <<')' << endl;
//    os <<"Couleur de fond : " << inColor << endl;
//    os <<"Couleur de bordure : " << borderColor << endl;
//    return os;
//}
