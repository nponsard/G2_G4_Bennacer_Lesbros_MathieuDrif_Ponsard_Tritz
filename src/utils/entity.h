#ifndef ENTITY_H
#define ENTITY_H

#include "minGL/figs/figure.h"
#include <vector>
#include "minGL/figs/pos.h"

struct entity
{
    unsigned entityHeight;
    unsigned entityWidth;
    pos position;

    unsigned entityFigID;
};

struct alien_entity
{
    unsigned entityHeight;
    unsigned entityWidth;

    unsigned entityFigID;
    unsigned pathStep;
    vector<pos> path;
};

#endif // ENTITY_H
