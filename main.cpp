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

void initSpaceInvaders(spaceInvaders & SI)
{
    figure player;
    player.Add(rectangle(pos(0, 0), 110, 30, KGreen, KGreen));
    player.Add(rectangle(pos(10, 30), 90, 10, KGreen, KGreen));
    player.Add(rectangle(pos(40, 40), 30, 20, KGreen, KGreen));
    player.Add(rectangle(pos(50, 60), 10, 10, KGreen, KGreen));


    figure invader;
    invader.Add(rectangle(pos(0, 460), 110, 10, KWhite, KWhite));
    invader.Add(rectangle(pos(20, 450), 70, 10, KWhite, KWhite));
    invader.Add(rectangle(pos(0, 450), 10, 10, KWhite, KWhite));
    invader.Add(rectangle(pos(100, 450), 10, 10, KWhite, KWhite));

    invader.Add(rectangle(pos(0, 440), 10, 10, KWhite, KWhite));
    invader.Add(rectangle(pos(100, 440), 10, 10, KWhite, KWhite));
    invader.Add(rectangle(pos(20, 440), 10, 10, KWhite, KWhite));
    invader.Add(rectangle(pos(80, 440), 10, 10, KWhite, KWhite));

    invader.Add(rectangle(pos(60, 430), 20, 10, KWhite, KWhite));
    invader.Add(rectangle(pos(30, 430), 20, 10, KWhite, KWhite));

    invader.Add(rectangle(pos(10, 470), 20, 10, KWhite, KWhite));
    invader.Add(rectangle(pos(80, 470), 20, 10, KWhite, KWhite));
    invader.Add(rectangle(pos(40, 470), 30, 10, KWhite, KWhite));

    invader.Add(rectangle(pos(20, 480), 70, 10, KWhite, KWhite));

    invader.Add(rectangle(pos(30, 490), 10, 10, KWhite, KWhite));
    invader.Add(rectangle(pos(70, 490), 10, 10, KWhite, KWhite));

    invader.Add(rectangle(pos(20, 500), 10, 10, KWhite, KWhite));
    invader.Add(rectangle(pos(80, 500), 10, 10, KWhite, KWhite));




    figure playerTorpedo;
    playerTorpedo.Add(rectangle(pos(352, 180), 5, 30, KWhite, KWhite));


    figure invadersTorpedo;
    invadersTorpedo.Add(rectangle(pos(252, 180), 5, 30, KWhite, KWhite));
    invadersTorpedo.Add(rectangle(pos(247, 210), 15, 5, KWhite, KWhite));

    SI.player = player;
    SI.invaders = invader;
    SI.invadersTorpedo = invadersTorpedo;
    SI.playerTorpedo = playerTorpedo;
}



void mainSpaceInvaders()
{
    spaceInvaders SI;
    initSpaceInvaders(SI);
    minGL Window(800, 600, "Space Invader", KBlack) ;
    Window.initGlut();
    Window.initGraphic();

    const chrono::duration<double, milli> frameDuration(16);//60fps

    map<char, bool> keyboardMap;
    while(true)
    {
        chrono::time_point<chrono::steady_clock> beg(chrono::steady_clock::now());


        keyboardMap = Window.get_key_2();

        if(keyboardMap.find(100) != keyboardMap.end() && keyboardMap[100] && SI.playerPos.getAbs() + 120 < Window.getWindowWidth())
            SI.playerPos.abs += 10;
        if(keyboardMap.find(113) != keyboardMap.end() && keyboardMap[113] && SI.playerPos.getAbs() > 10)
            SI.playerPos.abs -= 10;
        if(keyboardMap.find(115) != keyboardMap.end())
            SI.playerTorpedoPos.push_back(SI.playerPos + pos(0, 5));

        Window.clearScreen();
        Window << SI.invaders << SI.player + SI.playerPos << SI.playerTorpedo << SI.invadersTorpedo;
        Window.updateGraphic();

        //cout << SI.playerPos.abs << endl;
        chrono::time_point<chrono::steady_clock> end(chrono::steady_clock::now());
        chrono::duration<double, milli> diff(end - beg);
        if(diff < frameDuration)
            this_thread::sleep_for(frameDuration - diff);
        end = chrono::steady_clock::now();
        //cout << chrono::duration<double, milli>(end - beg).count() << endl;
    }





    Window.get_key();
}


int main()
{
    mainSpaceInvaders();
    return 0;
}
