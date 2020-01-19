#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "basefig.h"

#include "../tools/myexception.h"
#include "../graph/iminglinjectable.h"

class triangle : public baseFig
{
protected:
    virtual minGL & _Edit (minGL & Window) const throw (myexception);
public:
    triangle(const pos & pos1, const pos &pos2, const pos & pos3, const RGBcolor & borderCol_, const RGBcolor & fillCol_ = RGBcolor ());
    triangle (const baseFig &) throw (myexception);
    //operateur de décalage +
    triangle operator + (const pos & pos_) const {return baseFig::operator +(pos_);}
    friend triangle operator + (const pos & p, const triangle & t) {return t + p;}
    //operateur de reduction *
    triangle operator * (const float & f) const {return baseFig::operator *(f);}
    friend triangle operator * (const float & f, const triangle & t) {return t * f;}

    ~triangle () {}

};

#endif // TRIANGLE_H
