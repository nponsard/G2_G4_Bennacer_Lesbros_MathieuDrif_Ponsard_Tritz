/**
 *
 * @file    CstCodErr.h
 *
 * @authors D. Mathieu
 *
 * @date    28/08/2010
 *
 * @version V2.0
 *
 * @brief   Codes d'erreurs
 *
 **/
#if ! defined __CSTCODERR_H__
#define       __CSTCODERR_H__

#include <map>
#include <string>

namespace nsUtil
{
    enum {KNoExc          = 0,
          KNoError        = 0,

          kColorOutOfBounds = 100,

          KErrNoFile      = 252      , // erreur a l'ouverture du fichier
          KErrArg         = 253      , // erreur des arguments (nombre 
                                       //                       ou types)
          KExcStd         = 254      ,
          kExcInconnue    = -1,

          kErrTooHight    = 300,
          kErrTooRight    = 301,
          kErrFontSize    = 302,
          kNoTriangle     = 303,
          kNoLine         = 304,
          kNoRectangle    = 305,
          kNoCircle       = 306,
          kTypeNotFound   = 307,
         };

    const std::map <unsigned, std::string> kError
    {
        {kErrTooHight, "trop haut"},
        {kErrTooRight, "trop à droite"},
        {kErrFontSize, "taille de police pas bonne"},
        {kNoTriangle, "pas le bon nombre de pts pour la construction du triangle"},
        {kNoLine, "pas le bon nombre de pts pour la construction d'une ligne"},
        {kNoRectangle, "pas le bon nombre de pts pour la construction d'un rectangle"},
        {kNoCircle, "pas le bon nombre de pts pour la construction d'un cercle"},
        {kTypeNotFound, "instanciation impossible : pas le bon type"},
    };
} // namespace nsUtil

#endif        /* __CSTCODERR_H__ */
