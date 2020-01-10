#ifndef SPACEINVADERS_H
#define SPACEINVADERS_H

#include <vector>
#include <chrono>
#include "minGL/figs/figure.h"
#include "entity.h"


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
    unsigned bestScore;
    unsigned scoreStep;
    unsigned scoreStepBonusInvaders;
    unsigned scoreForMissileDestruction;
    unsigned torpedoVelocity;
    unsigned invadersVelocity;
    unsigned invadersMaxVelocity;
    unsigned invadersVelocityStep;
    unsigned wave;
    unsigned upgradeVelocity;

    std::vector<std::pair<std::string, unsigned>> bestScores;

    bool InvadersRight = true;

    entity invaders;
    entity player;
    entity playerTorpedo;
    entity invadersTorpedo;
    entity bonusInvader;

    entity lifeUpgrade;
    entity shootSpeedUpgrade;
    entity scoreUpgrade;

    pos playerPos;
    pos bonusInvaderPos;
    std::vector<pos> invadersPos;
    std::vector<pos> playerTorpedoPos;
    std::vector<pos> invadersTorpedoPos;

    std::vector<std::pair<pos, short>> UpgradePos;
    std::vector<figure> upgradeTypes;
};
void initSpaceInvadersFigs(spaceInvaders &SI);

#endif // SPACEINVADERS_H
