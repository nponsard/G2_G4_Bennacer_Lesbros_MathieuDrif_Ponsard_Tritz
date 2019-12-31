#ifndef SPACEINVADERS_H
#define SPACEINVADERS_H

#include <vector>
#include <chrono>
#include "figs/figure.h"

struct spaceInvaders
{
    std::chrono::duration<int, std::milli> shot;
    std::chrono::time_point<std::chrono::steady_clock> lastShot;

    std::chrono::duration<int, std::milli> invadersShot;
    std::chrono::time_point<std::chrono::steady_clock> invadersLastShot;

    std::chrono::duration<int, std::milli> bonusInvaders;
    std::chrono::time_point<std::chrono::steady_clock> LastBonusInvaders;



    unsigned lives;
    unsigned score;
    unsigned scoreStep;
    unsigned scoreForMissileDestruction;
    unsigned torpedoVelocity;
    unsigned invadersVelocity;
    unsigned invadersMaxVelocity;
    unsigned invadersVelocityStep;

    bool InvadersRight = true;

    figure invaders;
    figure player;
    figure playerTorpedo;
    figure invadersTorpedo;
    figure bonusInvader;

    pos playerPos;
    std::vector<pos> invadersPos;
    std::vector<pos> playerTorpedoPos;
    std::vector<pos> invadersTorpedoPos;
};

#endif // SPACEINVADERS_H
