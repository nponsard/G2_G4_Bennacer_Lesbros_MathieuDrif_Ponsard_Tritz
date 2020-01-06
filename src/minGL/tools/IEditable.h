/**
 *
 * @file    CEditable.h
 *
 * @authors D. Mathieu, M. Laporte
 *
 * @date    16/03/2009
 *
 * @version V2.0
 *
 * @brief   declaration de la classe CEditable dans nsUtil
 *
 **/
#if !defined __CEDITABLE_H__
#define      __CEDITABLE_H__

#include <iostream>

namespace nsUtil
{
    class IEditable;
    std::ostream & operator << (std::ostream & os, 
                                const IEditable & Obj);
    class IEditable
    {
      protected :
        virtual std::ostream & _Edit (std::ostream & os) const = 0;
    
      public :
     //   virtual ~IEditable (void);
        friend std::ostream & operator << (std::ostream & os, 
                                           const IEditable & Obj);
    }; // CEditable

} // nsUtil

#include "IEditable.hxx"

#endif     /* __CEDITABLE_H__ */

