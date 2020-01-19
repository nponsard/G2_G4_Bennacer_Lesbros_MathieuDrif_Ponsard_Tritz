#include "freeglut.h"
#include <ctime>
#include <cstdlib>

#include "nosFichiers/src/utils/music.h"

#include "nosFichiers/src/mainSpaceInvaders.h"

using namespace std;

///
/// \file main.cpp
/// \brief Main program
/// \author Clément MATHIEU--DRIF
/// \author Nils PONSARD
/// \author Hugo TRITZ
/// \author BENNACER Chakib
/// \author Raphaël LESBROS
///

///
/// \brief Initializes Glut and MinGl, creates a seed for randomness and launches the game.
/// \return
///

int main()
{
    //https://en.cppreference.com/w/cpp/utility/program/atexit
    atexit(killMusic);

    minGL window(1280, 720, "Space Invader", KBlack);
    window.initGlut();
    window.initGraphic();

    srand(time(NULL));
    mainSI(window);

    return 0;
}
