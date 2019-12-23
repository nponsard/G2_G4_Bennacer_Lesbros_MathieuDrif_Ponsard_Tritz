#ifndef SPACEINVADERS_H
#define SPACEINVADERS_H

#include <vector>
#include "figs/figure.h"

struct spaceInvaders
{
    figure invaders;
    figure player;
    figure playerTorpedo;
    figure invadersTorpedo;

    pos playerPos;
    std::vector<pos> invadersPos;
    std::vector<pos> playerTorpedoPos;
    std::vector<pos> invadersTorpedoPos;
};

#endif // SPACEINVADERS_H
