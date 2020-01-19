#include "display.h"

#include "nosFichiers/src/minGL/graph/pos.h"
#include "nosFichiers/src/minGL/figs/rectangle.h"
#include "nosFichiers/src/minGL/figs/figure.h"

#include "music.h"
#include "keyboardInput.h"//pour les constantes

#include <thread>

using namespace std;

///
/// \brief displays a figure at each position contained in a vector of positions
/// \param window : window on which the pictures are printed
/// \param positions : vector of positions where the picture must be displayed
/// \param fig : figure to be displayed
///
///
void display(minGL &window, const vector<pos> &positions, const figure &fig)
{
    for (vector<pos>::const_iterator it(positions.begin()); it != positions.end(); ++it)
        window << fig + *it;
}

///
/// \brief displays a figure at each position contained in a vector of pairs containing positions and the type of the upgrade(only works for the upgrades)
/// \param window : window on which the pictures are printed
/// \param upgrades : vector pairs containing the positions where the picture must be displayed
/// \param figures : vector of figures to be displayed
///

void display(minGL &window, const vector<pair<pos, short>> &upgrades, const vector<figure> &figures)
{
    for (vector<pair<pos, short>>::const_iterator it(upgrades.begin()); it != upgrades.end(); ++it)
        window << figures[it->second] + it->first;
}

///
/// \brief displays a figure at each position contained in a vector of pairs containing positions (only works for the invaders)
/// \param window : window on which the pictures are printed
/// \param positions : vector of pairs containig the positions where the picture must be displayed
/// \param fig : figure to be displayed
///

void display(minGL &window, const vector<pair<pos, unsigned>> &positions, const figure &fig)
{
    for (vector<pair<pos, unsigned>>::const_iterator it(positions.begin()); it != positions.end(); ++it)
        window << fig + it->first;
}

///
/// \brief displays the torpedos, the ennemies and the player on the screen
/// \param window : the window on which the pictures are printed
/// \param SI : the struct containing all the useful variables (including the positions of the torpedoes, the ennemies and the player)
///

void displaySpace(minGL &window, const spaceInvaders &SI)
{
    display(window, SI.invadersPos, SI.invaders.entityFig);
    display(window, SI.playerTorpedoPos, SI.playerTorpedo.entityFig);
    display(window, SI.invadersTorpedoPos, SI.invadersTorpedo.entityFig);
    if (!(SI.bonusInvaderPos == pos(0, 0)))
        window << SI.bonusInvader.entityFig + SI.bonusInvaderPos;
    display(window, SI.UpgradePos, SI.upgrades.entityFigs);

    window << SI.player.entityFig + SI.playerPos;
}

///
/// \brief displays spaces which will be filled with text on the screen
/// \param window : window on which the HUD will be printed
/// \param SI : struct containing all the useful variables (including the picture of the player, used to show the lifes remaining)
///

void displayHUD(minGL &window, const spaceInvaders &SI)
{
    window << rectangle(pos(0, window.getWindowHeight()), pos(window.getWindowWidth() - 1, window.getWindowHeight() - 70), KGreen, KBlack);
    window << rectangle(pos(0, 0), pos(window.getWindowWidth() - 1, 50), KGreen, KBlack);
    window << SI.player.entityFig * 0.5 + pos(10, 8);
}

///
/// \brief displays text to show the score, the lives remaining, the wave number and the number of invaders remaining on the screen
/// \param window : window on which the texte will be printed
/// \param SI : struct containing all the useful variables (including the wave number, the score, the lives remaining and the number of invaders alive)
///

void fillHUD(minGL &window, const spaceInvaders &SI)
{
    window.displayText(75, 12, to_string(SI.lives));

    window.displayText(5, window.getWindowHeight() - 40, "Score : ");
    window.displayText(80, window.getWindowHeight() - 40, to_string(SI.score));

    window.displayText(window.getWindowWidth() / 2 - 40, window.getWindowHeight() - 40, "Wave : ");
    window.displayText(window.getWindowWidth() / 2 + 30, window.getWindowHeight() - 40, to_string(SI.wave));

    window.displayText(window.getWindowWidth() - 130, window.getWindowHeight() - 40, "Invaders : ");
    window.displayText(window.getWindowWidth() - 25, window.getWindowHeight() - 40, to_string(SI.invadersPos.size()));
}

///
/// \brief Displays the menu screen and get the keyboard inputs to leave the pause screen if enter is pressed
/// \param SI : struct containing all the useful variables (including the invader's picture and his score)
/// \param window : window on which the menu screen will be printed
/// \param frameDuration : time between each frame
/// \return returns the key pressed if it is Enter (which will begin the game) or Escape (which will leave the game)
///

keyType SpaceInvadersMenu(const spaceInvaders &SI, minGL &window, const chrono::duration<double, milli> frameDuration)
{
    keyType key(0, false);
    double minInvaderSize(5.0), maxInvaderSize(5.5);
    bool bigger(true);
    double invaderSize(maxInvaderSize);
    while (key == keyType(0, false))
    {
        chrono::time_point<chrono::steady_clock> beg(chrono::steady_clock::now());

        window.clearScreen();
        window << SI.invaders.entityFig * invaderSize + pos(window.getWindowWidth() / 2 - (5 * 110), window.getWindowHeight() / 2);
        window.updateGraphic();

        window.displayText(window.getWindowWidth() - 400, window.getWindowHeight() / 2 + 260, "Leaderboard : ");

        for (unsigned i(0); i < SI.bestScores.size() && i < 3; ++i)
        {
            window.displayText(window.getWindowWidth() - 400, window.getWindowHeight() / 2 + 220 - (25 * i), SI.bestScores[i].first);
            window.displayText(window.getWindowWidth() - 370, window.getWindowHeight() / 2 + 220 - (25 * i), ":");
            window.displayText(window.getWindowWidth() - 350, window.getWindowHeight() / 2 + 220 - (25 * i), to_string(SI.bestScores[i].second));
        }

        window.displayText(window.getWindowWidth() - 600, window.getWindowHeight() / 2, "Press ENTER to play, or ESCAPE to quit");

        window.displayText(50, window.getWindowHeight() - 70, "Last score : ");
        window.displayText(200, window.getWindowHeight() - 70, to_string(SI.score));

        if (window.isPressed(KEY_ENTER))
            key = KEY_ENTER;

        if (window.isPressed(KEY_ESCAPE))
            key = KEY_ESCAPE;

        if (bigger) //animation menu
        {
            invaderSize += 0.005;
            if (invaderSize >= maxInvaderSize)
                bigger = false;
        }
        else
        {
            invaderSize -= 0.005;
            if (invaderSize <= minInvaderSize)
                bigger = true;
        }

        chrono::time_point<chrono::steady_clock> end(chrono::steady_clock::now());
        chrono::duration<double, milli> diff(end - beg);
        if (diff < frameDuration)
            this_thread::sleep_for(frameDuration - diff);
    }

    return key;
}

///
/// \brief Displays the pause screen and check if the player press Enter to leave the pause
/// \param SI : the struct containing all the useful variables (including the player's picture and his score)
/// \param window : the window on which the pause screen will be printed
/// \param frameDuration : the time between each frame
///

void SIpause(const spaceInvaders &SI, minGL &window, const chrono::duration<double, milli> frameDuration, bool &iLoose, bool &playmusic)
{
    keyType key(0, false);
    while (key == keyType(0, false) && !iLoose)
    {
        chrono::time_point<chrono::steady_clock> beg(chrono::steady_clock::now());

        window.clearScreen();
        window << SI.player.entityFig * 2 + pos(100, 0);
        window.updateGraphic();
        window.displayText(window.getWindowWidth() - 600, window.getWindowHeight() / 2, "Press ENTER to resume game");
        window.displayText(window.getWindowWidth() - 600, window.getWindowHeight() / 2 - 20, "Press ESCAPE to quit");
        window.displayText(window.getWindowWidth() - 600, window.getWindowHeight() / 2 - 40, "Press SPACE to stop/play music");

        window.displayText(50, window.getWindowHeight() - 70, "Score : ");
        window.displayText(200, window.getWindowHeight() - 70, to_string(SI.score));

        if (window.isPressed(KEY_ENTER))
        {
            key = KEY_ENTER;
            window.resetKey(KEY_ENTER); // éviter répétition de touches
        }

        if (window.isPressed(KEY_ESCAPE))
        {
            iLoose = true;
            window.resetKey(KEY_ESCAPE); // éviter répétition de touches
        }
        if (window.isPressed(KEY_SPACE))
        {
            if (playmusic)
            {
                killMusic();
                playmusic = false;
            }
            else
            {
                startMusic();
                playmusic = true;
            }
            window.resetKey(KEY_SPACE);
        }
        chrono::time_point<chrono::steady_clock> end(chrono::steady_clock::now());
        chrono::duration<double, milli> diff(end - beg);
        if (diff < frameDuration)
            this_thread::sleep_for(frameDuration - diff);
    }
}

///
/// \brief Displays the screen in which the player can enter his name if he did a new highscore, and read the keyboard input to allow him to enter his name
/// \param window : window on which the input screen will be displayed, and contain the informations about the keyboard inputs
/// \param frameDuration : time between each frame
/// \param nbCharMax : the maximum size of the name
/// \return returns a string corresponding to the name input
///

string ReadName(minGL &window, const chrono::duration<double, milli> frameDuration, const unsigned &nbCharMax /*= 3*/)
{
    string name;
    keyType key(0, false);
    while (key == keyType(0, false) || name.size() == 0)
    {
        key = keyType(0, false);
        chrono::time_point<chrono::steady_clock> beg(chrono::steady_clock::now());

        window.clearScreen();
        window << rectangle(pos(window.getWindowWidth() / 2 - 100, window.getWindowHeight() / 2 - 25), 200, 50, KWhite, KBlack);
        window.updateGraphic();

        window.displayText(window.getWindowWidth() / 2 - 150, window.getWindowHeight() / 2 + 100, "New highscore, type your name : ");

        window.displayText(window.getWindowWidth() / 2 - 90, window.getWindowHeight() / 2 - 5, name);

        if (name.size() < nbCharMax)
        {
            //lecture des lettres uniquement (ascii : 65 - 90)
            bool pressed(false);
            for (char keyVal(65); !pressed && keyVal <= 90; ++keyVal)
            {
                if (window.isPressed(keyType(keyVal, false)) || window.isPressed(keyType(keyVal + 32, false))) //test majuscule et minuscule
                {
                    name.push_back(keyVal);
                    pressed = true;
                    window.resetKey(keyType(keyVal, false));      // éviter répétition de touches
                    window.resetKey(keyType(keyVal + 32, false)); // éviter répétition de touches
                }
            }
        }
        if (window.isPressed(KEY_RETURN))
            if (name.size() != 0)
            {
                name.pop_back();
                window.resetKey(KEY_RETURN); // éviter répétition de touches
            }

        if (window.isPressed(KEY_ENTER))
        {
            key = KEY_ENTER;
            window.resetKey(KEY_ENTER);
        }

        chrono::time_point<chrono::steady_clock> end(chrono::steady_clock::now());
        chrono::duration<double, milli> diff(end - beg);
        if (diff < frameDuration)
            this_thread::sleep_for(frameDuration - diff);
    }
    window.resetKey(KEY_ENTER); //éviter répétition de touches en arrivant au menu
    return name;
}


