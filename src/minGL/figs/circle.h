#ifndef CIRCLE_H
#define CIRCLE_H

#include "basefig.h"

#include "../tools/myexception.h"

class circle : public baseFig
{
protected:
    virtual minGL & _Edit (minGL & Window) const throw (myexception);
public:
    circle(const pos & pos_, const unsigned & rad, const RGBcolor & borderCol, const RGBcolor & inCol = RGBcolor ());
    circle (const baseFig &) throw (myexception);
    //operateur de décalage +
    circle operator + (const pos & pos_) const;
    friend circle operator + (const pos & p, const circle & t) {return t + p;}
    //operateur de reduction *
    circle operator * (const float & f) const {return baseFig::operator *(f);}
    friend circle operator * (const float & f, const circle & t) {return t * f;}
    ~circle () {}
};

#endif // CIRCLE_H
