#include "graph/rgbcolor.h"
#include "graph/mingl.h"
#include "graph/pos.h"
#include "figs/rectangle.h"
#include "figs/triangle.h"
#include "figs/circle.h"
#include "figs/figure.h"

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

void initSpaceInvaders(spaceInvaders &SI, const unsigned &height, const unsigned &width)
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

    figure playerTorpedo;
    playerTorpedo.Add(rectangle(pos(0, 0), 5, 30, KWhite, KWhite));

    figure invadersTorpedo;
    invadersTorpedo.Add(rectangle(pos(5, 0), 5, 30, KWhite, KWhite));
    invadersTorpedo.Add(rectangle(pos(0, 30), 15, 5, KWhite, KWhite));

    SI.invadersMovements = chrono::duration<int, milli>(1200);
    SI.invadersLastMove = chrono::time_point<chrono::steady_clock>(chrono::steady_clock::now());

    SI.shot = chrono::duration<int, milli>(800);
    SI.lastShot = chrono::time_point<chrono::steady_clock>(chrono::steady_clock::now());

    SI.player = player;
    SI.invaders = invader;
    SI.invadersTorpedo = invadersTorpedo;
    SI.playerTorpedo = playerTorpedo;

    SI.playerPos = pos(0, 50); //placement intial joueur

    //placement invaders
    unsigned Xshift, Yshift(55);
    for (unsigned i(0); i < 3; ++i)
    {
        Xshift = 0;
        while (Xshift + 55 /*invaderSize*/ + 110 /*marge*/ < width)
        {
            SI.invadersPos.push_back(pos(Xshift, height - 100 - (Yshift * i)));
            Xshift += 110 + 50; /*distance entre invaders*/
        }
    }
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

void displayScore(minGL &window)
{
    window << rectangle(pos(0, window.getWindowHeight()), pos(window.getWindowWidth() - 1, window.getWindowHeight() - 50), KGreen, KBlack);
    window << rectangle(pos(0, 0), pos(window.getWindowWidth() - 1, 50), KGreen, KBlack);
}

vector<pos>::iterator collisions(spaceInvaders &SI,
                                 pos &entity,
                                 vector<pos> &vec,
                                 const unsigned &entityHeight,
                                 const unsigned &VHeight,
                                 const unsigned &entityWidth,
                                 const unsigned &VWidth)
{
    vector<pos>::iterator it(vec.begin());
    while (it != vec.end())
    {
        if (entity.getOrd() + entityHeight >= it->getOrd() && entity.getOrd() + entityHeight <= it->getOrd() + VHeight)
            if (entity.getAbs() + entityWidth >= it->getAbs() && entity.getAbs() <= it->getAbs() + VWidth)
                return it;
        ++it;
    }
    return vec.end();
}

void process(spaceInvaders &SI, minGL & window, const unsigned &height, const unsigned &width, bool &iWin, bool &iLoose)
{
    //deplacement missiles
    vector<pos>::iterator it(SI.playerTorpedoPos.begin());
    while (it != SI.playerTorpedoPos.end())
    {
        if (it->getOrd() + 30 < height)
        {
            *it = *it + pos(0, 5);
            ++it;
        }
        else
            SI.playerTorpedoPos.erase(it);
    }

    it = SI.invadersTorpedoPos.begin();
    while (it != SI.invadersTorpedoPos.end())
    {
        if (it->getOrd() > 0)
        {
            *it = pos(it->getAbs(), it->getOrd() - 5);
            ++it;
        }
        else
            SI.invadersTorpedoPos.erase(it);
    }

    //collisions

    //invaders - playerTorpedo
    it = SI.playerTorpedoPos.begin();
    while (it != SI.playerTorpedoPos.end())
    {
        vector<pos>::iterator collisionIt(collisions(SI, *it, SI.invadersPos, 15, 15, 50, 50));
        if (collisionIt != SI.invadersPos.end())
        {
            SI.playerTorpedoPos.erase(it);
            SI.invadersPos.erase(collisionIt);
        }
        else
            ++it;
    }

    //invadersTorpedo - playerTorpedo
    it = SI.playerTorpedoPos.begin();
    while (it != SI.playerTorpedoPos.end())
    {
        vector<pos>::iterator collisionIt(collisions(SI, *it, SI.invadersTorpedoPos, 15, 15, 15, 15));
        if (collisionIt != SI.invadersTorpedoPos.end())
        {
            SI.playerTorpedoPos.erase(it);
            SI.invadersTorpedoPos.erase(collisionIt);
        }
        else
            ++it;
    }

    //invadersTorpedo - player
    if (collisions(SI, SI.playerPos, SI.invadersTorpedoPos, 55, 15, 110, 15) != SI.invadersTorpedoPos.end())
        iLoose = true;

    if (!iLoose)
    {
        //deplacement invaders et tirs
        //un invader choisi au hasard envoie un missile à chaque déplacement
        chrono::time_point<chrono::steady_clock> now(chrono::steady_clock::now());
        chrono::duration<double, milli> diff(now - SI.invadersLastMove);
        bool downShift(false);
        if (diff >= SI.invadersMovements && !iWin)
        {
            //SI.invadersPos.size() != 0 car win = false
            //trouver pos max invaders
            vector<pos>::iterator extremum(SI.invadersPos.begin());

            if (SI.InvadersRight)
            {
                for (vector<pos>::iterator it2(extremum + 1); it2 != SI.invadersPos.end(); ++it2)
                    if (it2->getAbs() > extremum->getAbs())
                        extremum = it2;

                if (extremum->getAbs() + 5 + 55 /*invaders size*/ < width)
                {
                    //deplacer tous les invaders
                    it = SI.invadersPos.begin();
                    while (it != SI.invadersPos.end())
                    {
                        *it = pos(it->getAbs() + 5, it->getOrd());
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

                if (extremum->getAbs() > 5)
                {
                    //deplacer tous les invaders
                    it = SI.invadersPos.begin();
                    while (it != SI.invadersPos.end())
                    {
                        *it = pos(it->getAbs() - 5, it->getOrd());
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

                if (extremum->getOrd() > 30 /*invader height*/ + 50 /*score height*/)
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

            //tir
            it = SI.invadersPos.begin() + (rand() % SI.invadersPos.size());
            //trouver l'invader le plus bas dans cette colonne
            for (vector<pos>::iterator it2(SI.invadersPos.begin()); it2 != SI.invadersPos.end(); ++it2)
                if (it2->getAbs() == it->getAbs() && it2->getOrd() < it->getOrd())
                    it = it2;

            SI.invadersTorpedoPos.push_back(pos(it->getAbs() + 27, it->getOrd()));

            SI.invadersLastMove = chrono::time_point<chrono::steady_clock>(chrono::steady_clock::now());
        }

        if (window.isPressed(RIGHT) && SI.playerPos.getAbs() + 120 < window.getWindowWidth())
            SI.playerPos.abs += 10;
        if (window.isPressed(LEFT) && SI.playerPos.getAbs() > 10)
            SI.playerPos.abs -= 10;
        if (window.isPressed(KeyS))
        {
            now = chrono::steady_clock::now();
            diff = now - SI.lastShot;
            if(diff >= SI.shot)
            {
                SI.playerTorpedoPos.push_back(SI.playerPos + pos(52, 50));
                SI.lastShot = chrono::time_point<chrono::steady_clock>(chrono::steady_clock::now());
            }
        }
    }
}

void mainSpaceInvaders()
{
    minGL window(1280, 720, "Space Invader", KBlack);
    window.initGlut();
    window.initGraphic();

    spaceInvaders SI;
    initSpaceInvaders(SI, window.getWindowHeight(), window.getWindowWidth());

    const chrono::duration<double, milli> frameDuration(16.6); //60fps
    map<char, bool> keyboardMap;

    bool iWin(false), iLoose(false);

    while (!iLoose && !iWin)
    {
        chrono::time_point<chrono::steady_clock> beg(chrono::steady_clock::now());





        window.clearScreen();
        process(SI, window, window.getWindowHeight(), window.getWindowWidth(), iWin, iLoose);
        displaySpace(window, SI);
        displayScore(window);

        window.updateGraphic();

        chrono::time_point<chrono::steady_clock> end(chrono::steady_clock::now());
        chrono::duration<double, milli> diff(end - beg);
        if (diff < frameDuration)
            this_thread::sleep_for(frameDuration - diff);
        end = chrono::steady_clock::now();
    }

    if (iLoose)
        cout << "Lost" << endl;
    else //iWin
        cout << "Won" << endl;
    //window.get_key();
}

int main()
{
    srand(time(NULL));
    mainSpaceInvaders();
    return 0;
}
