/**
 *
 * @file    CException.h
 *
 * @authors M. Laporte, D. Mathieu
 *
 * @date    23/03/2010
 *
 * @version V1.0
 *
 * @brief   Declaration de la classe CException
 *
 **/
#if ! defined __CEXCEPTION_H__
#define       __CEXCEPTION_H__

#include <string>
#include <iostream>
#include <exception>

#include "CstCodErr.h"
#include "IEditable.h"

namespace nsUtil
{
    class CException : public std::exception, public IEditable
    {
    protected:
        std::string m_Libelle;
        unsigned    m_CodErr;

      public :
        CException (const std::string & Libelle = std::string(), 
                    const unsigned      CodErr  = KNoExc)     throw ();
        virtual ~CException (void)                            throw ();

        const std::string & GetLibelle (void) const           throw ();
        unsigned            GetCodErr  (void) const           throw ();

        virtual const char* what() const                      throw ();

      protected :
        virtual std::ostream & _Edit (std::ostream & os = std::cerr) const;

    }; // CException
    
} // namespace nsUtil

#include "CException.hxx"

#endif        /* __CEXCEPTION_H__ */

