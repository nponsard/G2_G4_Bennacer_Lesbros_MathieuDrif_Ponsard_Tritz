#include "graph/rgbcolor.h"
#include "graph/mingl.h"
#include "graph/pos.h"
#include "figs/rectangle.h"
#include "figs/triangle.h"
#include "figs/circle.h"
#include "figs/figure.h"

using namespace std;



int main()
{
    minGL Window(800, 600, "Space Invader") ;
    Window.initGlut();
    Window.initGraphic();


    figure invader;
    invader.Add(rectangle(pos(100, 100), 110, 10, KBlack, KBlack));
    invader.Add(rectangle(pos(120, 90), 70, 10, KBlack, KBlack));
    invader.Add(rectangle(pos(100, 90), 10, 10, KBlack, KBlack));
    invader.Add(rectangle(pos(200, 90), 10, 10, KBlack, KBlack));

    invader.Add(rectangle(pos(100, 80), 10, 10, KBlack, KBlack));
    invader.Add(rectangle(pos(200, 80), 10, 10, KBlack, KBlack));
    invader.Add(rectangle(pos(120, 80), 10, 10, KBlack, KBlack));
    invader.Add(rectangle(pos(180, 80), 10, 10, KBlack, KBlack));

    invader.Add(rectangle(pos(160, 70), 20, 10, KBlack, KBlack));
    invader.Add(rectangle(pos(130, 70), 20, 10, KBlack, KBlack));

    invader.Add(rectangle(pos(110, 110), 20, 10, KBlack, KBlack));
    invader.Add(rectangle(pos(180, 110), 20, 10, KBlack, KBlack));
    invader.Add(rectangle(pos(140, 110), 30, 10, KBlack, KBlack));

    invader.Add(rectangle(pos(120, 120), 70, 10, KBlack, KBlack));

    invader.Add(rectangle(pos(130, 130), 10, 10, KBlack, KBlack));
    invader.Add(rectangle(pos(170, 130), 10, 10, KBlack, KBlack));

    invader.Add(rectangle(pos(120, 140), 10, 10, KBlack, KBlack));
    invader.Add(rectangle(pos(180, 140), 10, 10, KBlack, KBlack));


    figure player;
    player.Add(rectangle(pos(300, 100), 110, 30, KGreen, KGreen));
    player.Add(rectangle(pos(310, 130), 90, 10, KGreen, KGreen));
    player.Add(rectangle(pos(340, 140), 30, 20, KGreen, KGreen));
    player.Add(rectangle(pos(350, 160), 10, 10, KGreen, KGreen));

    figure playerTorpedo;
    playerTorpedo.Add(rectangle(pos(352, 180), 5, 30, KBlack, KBlack));


    figure invadersTorpedo;
    invadersTorpedo.Add(rectangle(pos(252, 180), 5, 30, KBlack, KBlack));
    invadersTorpedo.Add(rectangle(pos(247, 210), 15, 5, KBlack, KBlack));

    Window << invader << player << playerTorpedo << invadersTorpedo;
    Window.updateGraphic();
    Window.get_key();
    return 0;
}
