#ifndef ENTITY_H
#define ENTITY_H

#include "minGL/figs/figure.h"
#include <vector>

/*!
 *  \brief structure containing a figure and its corresponding height and width
 */
struct entity
{
    unsigned entityHeight;
    unsigned entityWidth;

    figure entityFig;
};

struct BonusEntity
{
    unsigned entityHeight;
    unsigned entityWidth;

    std::vector<figure> entityFigs;
};

#endif // ENTITY_H
