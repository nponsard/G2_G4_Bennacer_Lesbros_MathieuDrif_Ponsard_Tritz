/**
 *
 * @file    CException.cxx
 *
 * @authors M. Laporte, D. Mathieu
 *
 * @date    23/03/2010
 *
 * @version V1.0
 *
 * @brief  classe CException
 *
 **/
#include <iostream>

#include "CException.h"

using namespace std;

ostream & nsUtil::CException::_Edit (ostream & os) const
{ 
    return os << "Exception : " << m_Libelle << '\n'
              << "Code      : " << m_CodErr;

} // _Edit()

