#ifndef SPACEINVADERS_H
#define SPACEINVADERS_H

#include <vector>
#include <chrono>
#include "minGL/figs/figure.h"
#include "entity.h"

/*!
 * \brief struct containing every useful variable and the parameters used in the game
 */

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
    unsigned invadersMinVelocity;
    unsigned wave;
    unsigned upgradeVelocity;
    unsigned bonusInvaderVelocityFactor;

    std::vector<std::pair<std::string, unsigned>> bestScores;

    bool InvadersRight = true;

    entity invaders;
    entity player;
    entity playerTorpedo;
    entity invadersTorpedo;
    entity bonusInvader;

    BonusEntity upgrades;

    pos playerPos;
    pos bonusInvaderPos;
    std::vector<std::pair<pos, unsigned>> invadersPos;
    std::vector<pos> playerTorpedoPos;
    std::vector<pos> invadersTorpedoPos;

    std::vector<std::pair<pos, short>> UpgradePos;
};

void initSpaceInvadersFigs(spaceInvaders &SI);
void initSpaceInvaders(spaceInvaders &SI);
void invadersGeneration(spaceInvaders &SI, const unsigned &height, const unsigned &width);
bool collisions(pos &entity1, pos &entity2, const unsigned &height1, const unsigned &height2, const unsigned &width1, const unsigned &width2);

#endif // SPACEINVADERS_H
