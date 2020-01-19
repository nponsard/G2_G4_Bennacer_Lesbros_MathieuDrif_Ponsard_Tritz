#include "nosFichiers/src/utils/keyboardInput.h"

using namespace std;

///
/// \brief Reads the keyboard inputs and move the player accordingly
/// \param window : contains the inputs and the size of the window
/// \param SI : struct containing all the useful variables (including the cooldown between shoots and the vector containing the player's torpedo)
/// \param pause : boolean which become true if the player press the escape button
///

void ReadKeyboard(minGL &window, spaceInvaders &SI, bool &pause)
{
    if (window.isPressed(KEY_RIGHT) && SI.playerPos.getAbs() + SI.player.entityWidth + 10 < window.getWindowWidth())
        SI.playerPos.abs += 10;
    if (window.isPressed(KEY_LEFT) && SI.playerPos.getAbs() > 10)
        SI.playerPos.abs -= 10;
    if (window.isPressed(KEY_SPACE))
    {
        chrono::duration<double, milli> diff(chrono::steady_clock::now() - SI.lastShot);
        if (diff >= SI.shot)
        {
            SI.playerTorpedoPos.push_back(SI.playerPos + pos(52, 50));
            SI.lastShot = chrono::steady_clock::now();
        }
    }

    if (window.isPressed(KEY_ESCAPE))
        pause = true;
}
