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
    std::chrono::time_point<std::chrono::steady_clock> LastBonusInvader;



    unsigned lives;
    unsigned score;
    unsigned scoreStep;
    unsigned scoreStepBonusInvaders;
    unsigned scoreForMissileDestruction;
    unsigned torpedoVelocity;
    unsigned invadersVelocity;
    unsigned invadersMaxVelocity;
    unsigned invadersVelocityStep;
    unsigned wave;

    bool InvadersRight = true;

    figure invaders;
    figure player;
    figure playerTorpedo;
    figure invadersTorpedo;
    figure bonusInvader;

    pos playerPos;
    pos bonusInvaderPos;
    std::vector<pos> invadersPos;
    std::vector<pos> playerTorpedoPos;
    std::vector<pos> invadersTorpedoPos;
};

#endif // SPACEINVADERS_H
