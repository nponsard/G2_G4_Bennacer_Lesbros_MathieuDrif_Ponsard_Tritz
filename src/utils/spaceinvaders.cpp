#include "spaceinvaders.h"
#include "entity.h"
#include "minGL/figs/figure.h"
#include "minGL/figs/rectangle.h"
#include "minGL/figs/triangle.h"
#include "minGL/figs/circle.h"

///
/// \brief Initializes the entities which contain the figures for MinGl
/// \param SI : the struct containing the variables to initialize
///

void initSpaceInvadersFigs(spaceInvaders &SI)
{
    //player
    SI.player.entityWidth = 110;
    SI.player.entityHeight = 70;
    SI.player.entityFig.Add(rectangle(pos(0, 0), 110, 30, KGreen, KGreen));
    SI.player.entityFig.Add(rectangle(pos(10, 30), 90, 10, KGreen, KGreen));
    SI.player.entityFig.Add(rectangle(pos(40, 40), 30, 20, KGreen, KGreen));
    SI.player.entityFig.Add(rectangle(pos(50, 60), 10, 10, KGreen, KGreen));

    //invader
    SI.invaders.entityWidth = 55;
    SI.invaders.entityHeight = 40;
    SI.invaders.entityFig.Add(rectangle(pos(0, 15), 55, 5, KWhite, KWhite));
    SI.invaders.entityFig.Add(rectangle(pos(10, 10), 35, 5, KWhite, KWhite));
    SI.invaders.entityFig.Add(rectangle(pos(0, 10), 5, 5, KWhite, KWhite));
    SI.invaders.entityFig.Add(rectangle(pos(50, 10), 5, 5, KWhite, KWhite));

    SI.invaders.entityFig.Add(rectangle(pos(0, 5), 5, 5, KWhite, KWhite));
    SI.invaders.entityFig.Add(rectangle(pos(50, 5), 5, 5, KWhite, KWhite));
    SI.invaders.entityFig.Add(rectangle(pos(10, 5), 5, 5, KWhite, KWhite));
    SI.invaders.entityFig.Add(rectangle(pos(40, 5), 5, 5, KWhite, KWhite));

    SI.invaders.entityFig.Add(rectangle(pos(30, 0), 10, 5, KWhite, KWhite));
    SI.invaders.entityFig.Add(rectangle(pos(15, 0), 10, 5, KWhite, KWhite));

    SI.invaders.entityFig.Add(rectangle(pos(5, 20), 10, 5, KWhite, KWhite));
    SI.invaders.entityFig.Add(rectangle(pos(40, 20), 10, 5, KWhite, KWhite));
    SI.invaders.entityFig.Add(rectangle(pos(20, 20), 15, 5, KWhite, KWhite));

    SI.invaders.entityFig.Add(rectangle(pos(10, 25), 35, 5, KWhite, KWhite));

    SI.invaders.entityFig.Add(rectangle(pos(15, 30), 5, 5, KWhite, KWhite));
    SI.invaders.entityFig.Add(rectangle(pos(35, 30), 5, 5, KWhite, KWhite));

    SI.invaders.entityFig.Add(rectangle(pos(10, 35), 5, 5, KWhite, KWhite));
    SI.invaders.entityFig.Add(rectangle(pos(40, 35), 5, 5, KWhite, KWhite));

    //bonusInvader
    SI.bonusInvader.entityWidth = 160;
    SI.bonusInvader.entityHeight = 70;
    SI.bonusInvader.entityFig.Add(rectangle(pos(50, 60), 60, 10, KRed, KRed));

    SI.bonusInvader.entityFig.Add(rectangle(pos(30, 50), 100, 10, KRed, KRed));

    SI.bonusInvader.entityFig.Add(rectangle(pos(20, 40), 120, 10, KRed, KRed));

    SI.bonusInvader.entityFig.Add(rectangle(pos(10, 30), 20, 10, KRed, KRed));
    SI.bonusInvader.entityFig.Add(rectangle(pos(40, 30), 20, 10, KRed, KRed));
    SI.bonusInvader.entityFig.Add(rectangle(pos(70, 30), 20, 10, KRed, KRed));
    SI.bonusInvader.entityFig.Add(rectangle(pos(100, 30), 20, 10, KRed, KRed));
    SI.bonusInvader.entityFig.Add(rectangle(pos(130, 30), 20, 10, KRed, KRed));

    SI.bonusInvader.entityFig.Add(rectangle(pos(0, 20), 160, 10, KRed, KRed));
    SI.bonusInvader.entityFig.Add(rectangle(pos(20, 10), 30, 10, KRed, KRed));
    SI.bonusInvader.entityFig.Add(rectangle(pos(70, 10), 20, 10, KRed, KRed));
    SI.bonusInvader.entityFig.Add(rectangle(pos(110, 10), 30, 10, KRed, KRed));
    SI.bonusInvader.entityFig.Add(rectangle(pos(30, 0), 10, 10, KRed, KRed));
    SI.bonusInvader.entityFig.Add(rectangle(pos(120, 0), 10, 10, KRed, KRed));

    //playerTorpedo
    SI.playerTorpedo.entityWidth = 5;
    SI.playerTorpedo.entityHeight = 30;
    SI.playerTorpedo.entityFig.Add(rectangle(pos(0, 0), 5, 30, KWhite, KWhite));

    //invadersTorpedo
    SI.invadersTorpedo.entityWidth = 15;
    SI.invadersTorpedo.entityHeight = 30;
    SI.invadersTorpedo.entityFig.Add(rectangle(pos(5, 0), 5, 30, KWhite, KWhite));
    SI.invadersTorpedo.entityFig.Add(rectangle(pos(0, 30), 15, 5, KWhite, KWhite));

    //upgrades
    SI.lifeUpgrade.entityWidth = 30;
    SI.lifeUpgrade.entityHeight = 30;
    SI.lifeUpgrade.entityFig.Add(rectangle(pos(10,0), 10, 30, KGreen, KGreen));
    SI.lifeUpgrade.entityFig.Add(rectangle(pos(0,10), 30, 10, KGreen, KGreen));

    SI.shootSpeedUpgrade.entityWidth = 30;
    SI.shootSpeedUpgrade.entityHeight = 30;
    SI.shootSpeedUpgrade.entityFig.Add(triangle(pos(15,30), pos(15,15), pos(0,15), KYellow, KYellow));
    SI.shootSpeedUpgrade.entityFig.Add(triangle(pos(30,30), pos(15,15), pos(15,30), KYellow, KYellow));
    SI.shootSpeedUpgrade.entityFig.Add(triangle(pos(2,0), pos(27,18), pos(12,19), KYellow, KYellow));

    SI.scoreUpgrade.entityWidth = 30;
    SI.scoreUpgrade.entityHeight = 30;
    SI.scoreUpgrade.entityFig.Add(circle(pos(15,15), 15, RGBcolor({200, 200,   0}), KYellow));
    SI.scoreUpgrade.entityFig.Add(rectangle(pos(12,8), pos(18,22), KBlack, RGBcolor({200, 200,   0})));

    SI.upgradeTypes.push_back(SI.lifeUpgrade.entityFig);
    SI.upgradeTypes.push_back(SI.shootSpeedUpgrade.entityFig);
    SI.upgradeTypes.push_back(SI.scoreUpgrade.entityFig);
}
