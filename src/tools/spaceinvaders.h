#ifndef SPACEINVADERS_H
#define SPACEINVADERS_H

#include <vector>
#include <chrono>
#include "figs/figure.h"

struct spaceInvaders
{
    std::chrono::duration<int, std::milli> invadersMovements;
    std::chrono::time_point<std::chrono::steady_clock> invadersLastMove;

    std::chrono::duration<int, std::milli> shot;
    std::chrono::time_point<std::chrono::steady_clock> lastShot;

    unsigned lives;

    unsigned score;
    unsigned scoreStep;

    bool InvadersRight = true;

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
