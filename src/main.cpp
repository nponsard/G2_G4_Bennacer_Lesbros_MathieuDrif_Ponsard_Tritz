#include "graph/rgbcolor.h"
#include "graph/mingl.h"
#include "graph/pos.h"
#include "figs/rectangle.h"
#include "figs/triangle.h"
#include "figs/circle.h"
#include "figs/figure.h"

#include "freeglut.h"
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <thread>

#include "tools/spaceinvaders.h"

using namespace std;

const keyType UP({101, true});
const keyType DOWN({103, true});
const keyType LEFT({100, true});
const keyType RIGHT({102, true});
const keyType ESCAPE({27, false});
const keyType KeyS({115, false});
const keyType KEY_SPACE({32, false});

void initSpaceInvadersFigs(spaceInvaders &SI)
{
    figure player;
    player.Add(rectangle(pos(0, 0), 110, 30, KGreen, KGreen));
    player.Add(rectangle(pos(10, 30), 90, 10, KGreen, KGreen));
    player.Add(rectangle(pos(40, 40), 30, 20, KGreen, KGreen));
    player.Add(rectangle(pos(50, 60), 10, 10, KGreen, KGreen));

    figure invader;
    invader.Add(rectangle(pos(0, 15), 55, 5, KWhite, KWhite));
    invader.Add(rectangle(pos(10, 10), 35, 5, KWhite, KWhite));
    invader.Add(rectangle(pos(0, 10), 5, 5, KWhite, KWhite));
    invader.Add(rectangle(pos(50, 10), 5, 5, KWhite, KWhite));

    invader.Add(rectangle(pos(0, 5), 5, 5, KWhite, KWhite));
    invader.Add(rectangle(pos(50, 5), 5, 5, KWhite, KWhite));
    invader.Add(rectangle(pos(10, 5), 5, 5, KWhite, KWhite));
    invader.Add(rectangle(pos(40, 5), 5, 5, KWhite, KWhite));

    invader.Add(rectangle(pos(30, 0), 10, 5, KWhite, KWhite));
    invader.Add(rectangle(pos(15, 0), 10, 5, KWhite, KWhite));

    invader.Add(rectangle(pos(5, 20), 10, 5, KWhite, KWhite));
    invader.Add(rectangle(pos(40, 20), 10, 5, KWhite, KWhite));
    invader.Add(rectangle(pos(20, 20), 15, 5, KWhite, KWhite));

    invader.Add(rectangle(pos(10, 25), 35, 5, KWhite, KWhite));

    invader.Add(rectangle(pos(15, 30), 5, 5, KWhite, KWhite));
    invader.Add(rectangle(pos(35, 30), 5, 5, KWhite, KWhite));

    invader.Add(rectangle(pos(10, 35), 5, 5, KWhite, KWhite));
    invader.Add(rectangle(pos(40, 35), 5, 5, KWhite, KWhite));



    figure bonusInvader;
    bonusInvader.Add(rectangle(pos(50, 60), 60, 10, KRed, KRed));

    bonusInvader.Add(rectangle(pos(30, 50), 100, 10, KRed, KRed));

    bonusInvader.Add(rectangle(pos(20, 40), 120, 10, KRed, KRed));

    bonusInvader.Add(rectangle(pos(10, 30), 20, 10, KRed, KRed));
    bonusInvader.Add(rectangle(pos(40, 30), 20, 10, KRed, KRed));
    bonusInvader.Add(rectangle(pos(70, 30), 20, 10, KRed, KRed));
    bonusInvader.Add(rectangle(pos(100, 30), 20, 10, KRed, KRed));
    bonusInvader.Add(rectangle(pos(130, 30), 20, 10, KRed, KRed));

    bonusInvader.Add(rectangle(pos(0, 20), 160, 10, KRed, KRed));
    bonusInvader.Add(rectangle(pos(20, 10), 30, 10, KRed, KRed));
    bonusInvader.Add(rectangle(pos(70, 10), 20, 10, KRed, KRed));
    bonusInvader.Add(rectangle(pos(110, 10), 30, 10, KRed, KRed));
    bonusInvader.Add(rectangle(pos(30, 0), 10, 10, KRed, KRed));
    bonusInvader.Add(rectangle(pos(120, 0), 10, 10, KRed, KRed));




    figure playerTorpedo;
    playerTorpedo.Add(rectangle(pos(0, 0), 5, 30, KWhite, KWhite));

    figure invadersTorpedo;
    invadersTorpedo.Add(rectangle(pos(5, 0), 5, 30, KWhite, KWhite));
    invadersTorpedo.Add(rectangle(pos(0, 30), 15, 5, KWhite, KWhite));

    SI.player = player;
    SI.invaders = invader;
    SI.invadersTorpedo = invadersTorpedo;
    SI.playerTorpedo = playerTorpedo;
    SI.bonusInvader = bonusInvader;
}

void invadersGeneration(spaceInvaders &SI, const unsigned &height, const unsigned &width)
{
    unsigned Xshift, Yshift(55);
    for (unsigned i(0); i < 4; ++i)
    {
        Xshift = 0;
        while (Xshift + 55 /*invaderSize*/ + 110 /*marge*/ < width)
        {
            SI.invadersPos.push_back(pos(Xshift, height - 200 - (Yshift * i)));
            Xshift += 110 + 50; /*distance entre invaders*/
        }
    }
}

void initSpaceInvaders(spaceInvaders &SI)
{
    initSpaceInvadersFigs(SI);

    SI.invadersVelocity = 1;
    SI.invadersMaxVelocity = 5;
    SI.invadersVelocityStep = 0;

    SI.shot = chrono::duration<int, milli>(200);
    SI.lastShot = chrono::steady_clock::now();

    SI.invadersShot = chrono::duration<int, milli>(900);
    SI.invadersLastShot = chrono::steady_clock::now();

    SI.playerPos = pos(0, 50); //placement intial joueur
    SI.lives = 3;
    SI.score = 0;
    SI.scoreForMissileDestruction = 50;
    SI.scoreStep = 100;
    SI.torpedoVelocity = 20;
}

void display(minGL &window, const vector<pos> &positions, const figure &fig)
{
    for (vector<pos>::const_iterator it(positions.begin()); it != positions.end(); ++it)
        window << fig + *it;
}

void displaySpace(minGL &window, const spaceInvaders &SI)
{
    display(window, SI.invadersPos, SI.invaders);
    display(window, SI.playerTorpedoPos, SI.playerTorpedo);
    display(window, SI.invadersTorpedoPos, SI.invadersTorpedo);
    window << SI.player + SI.playerPos;
}

void displayHUD(minGL &window, const spaceInvaders &SI)
{
    window << rectangle(pos(0, window.getWindowHeight()), pos(window.getWindowWidth() - 1, window.getWindowHeight() - 50), KGreen, KBlack);
    window << rectangle(pos(0, 0), pos(window.getWindowWidth() - 1, 50), KGreen, KBlack);
    window << SI.player * 0.5 + pos(10, 8);
}

void fillHUD(minGL &window, const spaceInvaders &SI)
{
    //vies
    window.displayText(75, 12, to_string(SI.lives));
    window.displayText(5, window.getWindowHeight() - 25, "Score : ");
    window.displayText(85, window.getWindowHeight() - 25, to_string(SI.score));
}

bool collisions(spaceInvaders &SI,
                pos &entity1,
                pos &entity2,
                const unsigned &entityHeight,
                const unsigned &VHeight,
                const unsigned &entityWidth,
                const unsigned &VWidth)
{
    if (entity1.getOrd() + entityHeight >= entity2.getOrd() && entity1.getOrd() + entityHeight <= entity2.getOrd() + VHeight)
        if (entity1.getAbs() + entityWidth >= entity2.getAbs() && entity1.getAbs() <= entity2.getAbs() + VWidth)
            return true;

    return false;
}

void process(spaceInvaders &SI, minGL &window, const unsigned &height, const unsigned &width, bool &iLoose, bool &iWin)
{
    //deplacement missiles joueur
    vector<pos>::iterator it(SI.playerTorpedoPos.begin());
    while (it != SI.playerTorpedoPos.end())
    {
        bool collision(false);                                                              //collision avec un mur, un invader ou un missile d'invader
        for (unsigned tempMove(0); !collision && tempMove < SI.torpedoVelocity; ++tempMove) //deplacer par pas de 1 pour verifier les collisions meme quand la vitesse des missiles est élevée
        {
            if (it->getOrd() + 1 + 30 /*taille missile*/ < height)
            {
                *it = *it + pos(0, 1); //déplacement

                //collision avec un invader
                for (vector<pos>::iterator itInvadersPos(SI.invadersPos.begin()); !collision && itInvadersPos != SI.invadersPos.end(); ++itInvadersPos)
                {
                    collision = collisions(SI, *it, *itInvadersPos, 15, 15, 50, 50);
                    if (collision)
                    {
                        SI.playerTorpedoPos.erase(it);
                        SI.invadersPos.erase(itInvadersPos);
                        SI.score += SI.scoreStep;
                        SI.scoreStep += 20;
                        if (SI.invadersVelocity + SI.invadersVelocityStep <= SI.invadersMaxVelocity)
                            SI.invadersVelocity += SI.invadersVelocityStep;
                        else if (SI.invadersVelocity != SI.invadersMaxVelocity)
                            SI.invadersVelocity = SI.invadersMaxVelocity;
                    }
                }

                if (!collision)
                {
                    //collision avec un missile
                    for (vector<pos>::iterator itInvadersTorpedoPos(SI.invadersTorpedoPos.begin()); !collision && itInvadersTorpedoPos != SI.invadersTorpedoPos.end(); ++itInvadersTorpedoPos)
                    {
                        collision = collisions(SI, *it, *itInvadersTorpedoPos, 15, 15, 15, 15);
                        if (collision)
                        {
                            SI.playerTorpedoPos.erase(it);
                            SI.invadersTorpedoPos.erase(itInvadersTorpedoPos);
                            SI.score += SI.scoreForMissileDestruction;
                        }
                    }
                }
            }
            else //collision avec le mur
            {
                SI.playerTorpedoPos.erase(it);
                collision = true;
            }
        }
        if (!collision)
            ++it;
    }

    //deplacement des missiles invaders
    it = SI.invadersTorpedoPos.begin();
    while (it != SI.invadersTorpedoPos.end())
    {
        bool collision(false);
        for (unsigned tempMove(0); !collision && tempMove < SI.torpedoVelocity; ++tempMove) //deplacer par pas de 1 pour verifier collisions meme quand vitesse élevée
        {
            if (it->getOrd() > 1)
            {
                *it = pos(it->getAbs(), it->getOrd() - 1);                      //déplacement
                collision = collisions(SI, *it, SI.playerPos, 15, 55, 15, 110); //collision avec le joueur
                if (collision)
                {
                    SI.invadersTorpedoPos.erase(it);
                    if (--SI.lives == 0)
                        iLoose = true;
                }
            }
            else //collision avec le mur
            {
                SI.invadersTorpedoPos.erase(it);
                collision = true;
            }
        }
        if (!collision)
            ++it;
    }

    if (SI.invadersPos.size() == 0)
        iWin = true;
    else if (!iLoose)
    {
        //tir
        //un invader choisi au hasard envoie un missile
        chrono::time_point<chrono::steady_clock> now(chrono::steady_clock::now());
        chrono::duration<double, milli> diff(now - SI.invadersLastShot);
        if (diff >= SI.invadersShot)
        {
            it = SI.invadersPos.begin() + (rand() % SI.invadersPos.size()); //choix d'un invader
            //trouver l'invader le plus bas dans cette colonne
            for (vector<pos>::iterator it2(SI.invadersPos.begin()); it2 != SI.invadersPos.end(); ++it2)
                if (it2->getAbs() == it->getAbs() && it2->getOrd() < it->getOrd())
                    it = it2;

            SI.invadersTorpedoPos.push_back(pos(it->getAbs() + 27, it->getOrd()));

            SI.invadersLastShot = chrono::steady_clock::now();
        }

        //déplacement
        bool downShift(false);
        //SI.invadersPos.size() != 0 car win = false
        //trouver pos max invaders
        vector<pos>::iterator extremum(SI.invadersPos.begin());

        if (SI.InvadersRight)
        {
            for (vector<pos>::iterator it2(extremum + 1); it2 != SI.invadersPos.end(); ++it2)
                if (it2->getAbs() > extremum->getAbs())
                    extremum = it2;

            if (extremum->getAbs() + SI.invadersVelocity + 55 /*invaders size*/ < width)
            {
                //deplacer tous les invaders
                it = SI.invadersPos.begin();
                while (it != SI.invadersPos.end())
                {
                    *it = pos(it->getAbs() + SI.invadersVelocity, it->getOrd());
                    ++it;
                }
            }
            else
            {
                SI.InvadersRight = false;
                downShift = true;
            }
        }
        else
        {
            for (vector<pos>::iterator it2(SI.invadersPos.begin() + 1); it2 != SI.invadersPos.end(); ++it2)
                if (it2->getAbs() < extremum->getAbs())
                    extremum = it2;

            if (extremum->getAbs() > SI.invadersVelocity)
            {
                //deplacer tous les invaders
                it = SI.invadersPos.begin();
                while (it != SI.invadersPos.end())
                {
                    *it = pos(it->getAbs() - SI.invadersVelocity, it->getOrd());
                    ++it;
                }
            }
            else
            {
                SI.InvadersRight = true;
                downShift = true;
            }
        }

        if (downShift)
        {
            extremum = SI.invadersPos.begin();
            for (vector<pos>::iterator it2(SI.invadersPos.begin() + 1); it2 != SI.invadersPos.end(); ++it2)
                if (it2->getOrd() < extremum->getOrd())
                    extremum = it2;

            if (extremum->getOrd() > 30 /*invader height*/ + 50 /*score height*/ + 70 /*player height*/)
            {
                //deplacer tous les invaders
                it = SI.invadersPos.begin();
                while (it != SI.invadersPos.end())
                {
                    *it = pos(it->getAbs(), it->getOrd() - 30);
                    ++it;
                }
            }
            else
                iLoose = true;
        }

        //lecture clavier
        if (window.isPressed(RIGHT) && SI.playerPos.getAbs() + 120 < window.getWindowWidth())
            SI.playerPos.abs += 10;
        if (window.isPressed(LEFT) && SI.playerPos.getAbs() > 10)
            SI.playerPos.abs -= 10;
        if (window.isPressed(KEY_SPACE))
        {
            now = chrono::steady_clock::now();
            diff = now - SI.lastShot;
            if (diff >= SI.shot)
            {
                SI.playerTorpedoPos.push_back(SI.playerPos + pos(52, 50));
                SI.lastShot = chrono::steady_clock::now();
            }
        }
    }
}

void mainSpaceInvaders(minGL &window)
{

    spaceInvaders SI, SIBase;
    initSpaceInvaders(SI);
    invadersGeneration(SI, window.getWindowHeight(), window.getWindowWidth());
    SIBase = SI;

    const chrono::duration<double, milli> frameDuration(33.3); //30fps

    bool iLoose(false), iWin(false);

    while (!iLoose)
    {
        chrono::time_point<chrono::steady_clock> beg(chrono::steady_clock::now());

        process(SI, window, window.getWindowHeight(), window.getWindowWidth(), iLoose, iWin);

        if (iWin)
        {
            iWin = false;
            SI = SIBase;
            window.displayText(window.getWindowWidth() / 2 - 50, window.getWindowHeight() / 2, "vague suivante...");
            this_thread::sleep_for(chrono::duration<int, milli>(1000));
        }

        window.clearScreen();
        displaySpace(window, SI);
        displayHUD(window, SI);
        window.updateGraphic();
        fillHUD(window, SI);

        chrono::time_point<chrono::steady_clock> end(chrono::steady_clock::now());
        chrono::duration<double, milli> diff(end - beg);
        if (diff < frameDuration)
            this_thread::sleep_for(frameDuration - diff);
    }

    if (iLoose)
        cout << "Lost" << endl;
    else //iWin
        cout << "Won" << endl;
}

int main()
{
    minGL window(1280, 720, "Space Invader", KBlack);
    window.initGlut();
    window.initGraphic();

    srand(time(NULL));
    mainSpaceInvaders(window);

    return 0;
}
