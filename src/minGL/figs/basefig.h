#ifndef BASEFIG_H
#define BASEFIG_H

#include <map>

//#include "../tools/IEditable.h"
#include "pos.h"
#include "../graph/rgbcolor.h"
#include "../graph/iminglinjectable.h"


class baseFig : /*public nsUtil::IEditable,*/ public IminGlInjectable
{
protected :
//    std::map <std::string, pos> remarkablePt;
//    RGBcolor borderColor, inColor;
//    virtual std::ostream & _Edit (std::ostream & os = std::cout) const;
    virtual minGL & _Edit (minGL & Window) const throw (myexception) {return Window;}
    baseFig (const std::map<std::string, pos>&, const RGBcolor &, const RGBcolor &);
public:
    baseFig();
~baseFig () {}
    //baseFig (const baseFig &);

    //operateur de décalage +
    /*virtual*/ baseFig operator + (const pos & pos_) const;
    friend baseFig operator + (const pos &, const baseFig &); //pour la commutativité

    //operateur de reduction *
    /*virtual*/ baseFig operator * (const float & f) const;
    friend baseFig operator * (const float & f, const baseFig &); //pour la commutativité

    //donnes membres
    //doivent être public :/ sinon ça pose des soucis dans les conversions
    std::map <std::string, pos> remarkablePt;
    RGBcolor borderColor, inColor;
    std::string name; //ajouter pour l'introspection
    std::string getName() const;
};

#endif // BASEFIG_H
