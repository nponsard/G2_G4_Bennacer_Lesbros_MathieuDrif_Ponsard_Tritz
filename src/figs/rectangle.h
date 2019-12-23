#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "basefig.h"

#include "../tools/myexception.h"

class rectangle : public baseFig
{
protected:
    virtual minGL & _Edit (minGL & Window) const throw (myexception);
public:
    rectangle(const pos & pos1, const pos & pos2, const RGBcolor & borderCol, const RGBcolor & inCol = RGBcolor ());
    rectangle(const pos & pos, const unsigned & width, const unsigned & height, const RGBcolor & borderCol, const RGBcolor & inCol = RGBcolor ());

    rectangle (const baseFig &) throw (myexception);
    //operateur de décalage +
    rectangle operator + (const pos & pos_) const {return baseFig::operator +(pos_);}
    friend rectangle operator + (const pos & p, const rectangle & t) {return t + p;}
    //operateur de reduction *
    rectangle operator * (const float & f) const {return baseFig::operator *(f);}
    friend rectangle operator * (const float & f, const rectangle & t) {return t * f;}
    ~rectangle () {}
};

#endif // RECTANGLE_H
