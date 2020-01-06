/**
 *
 * @file    CEditable.hxx
 *
 * @authors D. Mathieu, M. Laporte
 *
 * @date    17/03/2010
 *
 * @version V2.0
 *
 **/
#if !defined __CEDITABLE_HXX__
#define      __CEDITABLE_HXX__

#include <iostream>

#include "IEditable.h"

//inline nsUtil::IEditable::~IEditable (void) {}

inline 
std::ostream & nsUtil::operator << (std::ostream & os, 
                                    const IEditable & Obj)
{
    return Obj._Edit (os);

} // operator <<

#endif      /* __CEDITABLE_HXX__ */

