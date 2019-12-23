#include "graph/rgbcolor.h"
#include "graph/mingl.h"
#include "graph/pos.h"
#include "figs/rectangle.h"
#include "figs/triangle.h"
#include "figs/circle.h"
#include "figs/figure.h"

#include <chrono>
#include <thread>

#include "tools/spaceinvaders.h"

using namespace std;

void initSpaceInvaders(spaceInvaders & SI, const unsigned & height, const unsigned & width)
{
    figure player;
    player.Add(rectangle(pos(0, 0), 110, 30, KGreen, KGreen));
    player.Add(rectangle(pos(10, 30), 90, 10, KGreen, KGreen));
    player.Add(rectangle(pos(40, 40), 30, 20, KGreen, KGreen));
    player.Add(rectangle(pos(50, 60), 10, 10, KGreen, KGreen));


    figure invader;
    invader.Add(rectangle(pos(0, 30), 110, 10, KWhite, KWhite));
    invader.Add(rectangle(pos(20, 20), 70, 10, KWhite, KWhite));
    invader.Add(rectangle(pos(0, 20), 10, 10, KWhite, KWhite));
    invader.Add(rectangle(pos(100, 20), 10, 10, KWhite, KWhite));

    invader.Add(rectangle(pos(0, 10), 10, 10, KWhite, KWhite));
    invader.Add(rectangle(pos(100, 10), 10, 10, KWhite, KWhite));
    invader.Add(rectangle(pos(20, 10), 10, 10, KWhite, KWhite));
    invader.Add(rectangle(pos(80, 10), 10, 10, KWhite, KWhite));

    invader.Add(rectangle(pos(60, 0), 20, 10, KWhite, KWhite));
    invader.Add(rectangle(pos(30, 0), 20, 10, KWhite, KWhite));

    invader.Add(rectangle(pos(10, 40), 20, 10, KWhite, KWhite));
    invader.Add(rectangle(pos(80, 40), 20, 10, KWhite, KWhite));
    invader.Add(rectangle(pos(40, 40), 30, 10, KWhite, KWhite));

    invader.Add(rectangle(pos(20, 50), 70, 10, KWhite, KWhite));

    invader.Add(rectangle(pos(30, 60), 10, 10, KWhite, KWhite));
    invader.Add(rectangle(pos(70, 60), 10, 10, KWhite, KWhite));

    invader.Add(rectangle(pos(20, 70), 10, 10, KWhite, KWhite));
    invader.Add(rectangle(pos(80, 70), 10, 10, KWhite, KWhite));




    figure playerTorpedo;
    playerTorpedo.Add(rectangle(pos(0, 0), 5, 30, KWhite, KWhite));


    figure invadersTorpedo;
    invadersTorpedo.Add(rectangle(pos(5, 0), 5, 30, KWhite, KWhite));
    invadersTorpedo.Add(rectangle(pos(0, 30), 15, 5, KWhite, KWhite));

    SI.player = player;
    SI.invaders = invader;
    SI.invadersTorpedo = invadersTorpedo;
    SI.playerTorpedo = playerTorpedo;

    SI.playerPos = pos(0, 50);

    SI.invadersPos.push_back(pos(0, height-150));
    SI.invadersTorpedoPos.push_back(pos(47, height-150));
}

void display(minGL & window, const vector<pos> & positions, const figure & fig)
{
    for(vector<pos>::const_iterator it(positions.begin()); it != positions.end(); ++it)
        window << fig + *it;
}

void displaySpace(minGL & window, const spaceInvaders & SI)
{
    display(window, SI.invadersPos, SI.invaders);
    display(window, SI.playerTorpedoPos, SI.playerTorpedo);
    display(window, SI.invadersTorpedoPos, SI.invadersTorpedo);
    window << SI.player + SI.playerPos;

}

void displayScore(minGL & window)
{
    window << rectangle(pos(0, window.getWindowHeight()), pos(window.getWindowWidth()-1, window.getWindowHeight() - 50), KGreen, KBlack);
    window << rectangle(pos(0, 0), pos(window.getWindowWidth()-1, 50), KGreen, KBlack);
}

void process(spaceInvaders & SI, const unsigned & height, const unsigned & width)
{
    vector<pos>::iterator it(SI.playerTorpedoPos.begin());
    while(it != SI.playerTorpedoPos.end())
    {
        if(it->getOrd() + 30 < height)
        {
            *it = *it + pos(0, 5);
            ++it;
        }
        else
            SI.playerTorpedoPos.erase(it);
    }

    it = SI.invadersTorpedoPos.begin();
    while(it != SI.invadersTorpedoPos.end())
    {
        if(it->getOrd() > 0)
        {
            *it = pos(it->getAbs(), it->getOrd() - 1);
            ++it;
        }
        else
            SI.invadersTorpedoPos.erase(it);
    }



    /*GESTION POSITION JOUEUR*/
}

void mainSpaceInvaders()
{
    minGL window(1280, 720, "Space Invader", KBlack) ;
    window.initGlut();
    window.initGraphic();

    spaceInvaders SI;
    initSpaceInvaders(SI, window.getWindowHeight(), window.getWindowWidth());

    const chrono::duration<double, milli> frameDuration(16);//60fps

    map<char, bool> keyboardMap;
    while(true)
    {
        chrono::time_point<chrono::steady_clock> beg(chrono::steady_clock::now());


        keyboardMap = window.get_key_2();/*faire une methode dans MINGL*/

        if(keyboardMap.find(100) != keyboardMap.end() && keyboardMap[100] && SI.playerPos.getAbs() + 120 < window.getWindowWidth())
            SI.playerPos.abs += 10;
        if(keyboardMap.find(113) != keyboardMap.end() && keyboardMap[113] && SI.playerPos.getAbs() > 10)
            SI.playerPos.abs -= 10;
        if(keyboardMap.find(115) != keyboardMap.end() && keyboardMap[115])
            SI.playerTorpedoPos.push_back(SI.playerPos + pos(52, 50));

        window.clearScreen();
        process(SI, window.getWindowHeight(), window.getWindowWidth());
        displaySpace(window, SI);
        displayScore(window);

        window.updateGraphic();

        chrono::time_point<chrono::steady_clock> end(chrono::steady_clock::now());
        chrono::duration<double, milli> diff(end - beg);
        if(diff < frameDuration)
            this_thread::sleep_for(frameDuration - diff);
        end = chrono::steady_clock::now();
        //cout << chrono::duration<double, milli>(end - beg).count() << endl;
    }
    window.get_key();
}


int main()
{
    mainSpaceInvaders();
    return 0;
}
