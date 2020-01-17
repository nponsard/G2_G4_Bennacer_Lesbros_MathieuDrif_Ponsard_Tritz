#ifndef ENTITY_H
#define ENTITY_H

#include "minGL/figs/figure.h"

/*!
 *  \brief structure containing a figure and its corresponding height and width
 */
struct entity
{
    unsigned entityHeight;
    unsigned entityWidth;

    figure entityFig;
};

#endif // ENTITY_H
