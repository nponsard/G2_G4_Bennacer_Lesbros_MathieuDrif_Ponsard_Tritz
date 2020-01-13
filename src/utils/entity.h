#ifndef ENTITY_H
#define ENTITY_H

#include "minGL/figs/figure.h"

/*!
 *  \brief struct associant une figure à une largeur et une hauteur
 *  
 * 
 */
struct entity
{
    unsigned entityHeight;
    unsigned entityWidth;

    figure entityFig;
};

#endif // ENTITY_H
