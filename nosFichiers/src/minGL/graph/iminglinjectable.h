#ifndef IMINGLINJECTABLE_H
#define IMINGLINJECTABLE_H

#include "mingl.h"
#include "../tools/myexception.h"

class IminGlInjectable
{
  protected :
    virtual minGL & _Edit (minGL & Window) const throw (myexception) = 0;

  public :
 //   virtual ~IminGlInjectable (void) {}
    friend minGL & operator << (minGL & Window,
                                       const IminGlInjectable & Obj)
    {
        return Obj._Edit (Window);
    }
}; // IminGlInjectable

#endif // IMINGLINJECTABLE_H
