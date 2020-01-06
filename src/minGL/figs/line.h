#ifndef LINE_H
#define LINE_H

#include "basefig.h"

#include "../tools/myexception.h"

class line : public baseFig
{
protected:
    virtual minGL & _Edit (minGL & Window) const throw (myexception);
public:


    line (const pos& pix1, const pos & pix2, const RGBcolor & fillCol = RGBcolor ());
    line (const baseFig &) throw (myexception);

    //operateur de décalage +
    line operator + (const pos & pos_) const {return baseFig::operator +(pos_);}
    friend line operator + (const pos & p, const line & t) {return t + p;}
    //operateur de reduction *
    line operator * (const float & f) const {return baseFig::operator *(f);}
    friend line operator * (const float & f, const line & t) {return t * f;}

    ~line () {}
};

#endif // LINE_H
