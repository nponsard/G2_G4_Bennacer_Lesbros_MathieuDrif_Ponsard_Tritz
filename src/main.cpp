#include "minGL/graph/rgbcolor.h"
#include "minGL/graph/mingl.h"
#include "minGL/graph/pos.h"
#include "minGL/figs/rectangle.h"
#include "minGL/figs/triangle.h"
#include "minGL/figs/circle.h"
#include "minGL/figs/figure.h"

#include "freeglut.h"
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <thread>

#include "utils/spaceinvaders.h"
#include "utils/loadconfig.h"

///
/// \file main.cpp
/// \brief Main program
/// \author Clément MATHIEU--DRIF
/// \author Nils PONSARD
/// \author Hugo TRITZ
/// \author BENNACER Chakib
/// \author Raphaël LESBROS
///

using namespace std;

///
/// \enum KeyTypes
/// \brief Constants corresponding to useful keys
///
const keyType KEY_UP({101, true});
const keyType KEY_DOWN({103, true});
const keyType KEY_LEFT({100, true});
const keyType KEY_RIGHT({102, true});
const keyType KEY_ESCAPE({27, false});
const keyType KEY_SPACE({32, false});
const keyType KEY_ENTER({13, false});

///
/// \brief Add invaders to the vector containing their pos until they fill their starting space
/// \param SI : the struct containing all useful variables (including the size of the invaders and a vector containing all invaders' positions)
/// \param height : the height of the space to fill with invaders
/// \param width : the width of the space to fill with invaders
///

void invadersGeneration(spaceInvaders &SI, const unsigned &height, const unsigned &width)
{
    unsigned Xshift, Yshift(55);
    for (unsigned i(0); i < 4; ++i)
    {
        Xshift = 0;
        while (Xshift + SI.invaders.entityWidth + (2 * SI.invaders.entityWidth) /*marge min*/ < width)
        {
            SI.invadersPos.push_back(pos(Xshift, height - 200 - (Yshift * i)));
            Xshift += 3 * SI.invaders.entityWidth; /*distance entre invaders*/
        }
    }
}

///
/// \brief initialize the variables contained in a SpaceInvaders struct
/// \param SI : the struct containing all the variables to initialize
///

void initSpaceInvaders(spaceInvaders &SI)
{
    initSpaceInvadersFigs(SI);

    map<string, string> conf(loadConfig("config.yaml"));

    SI.invadersVelocity = unsigned(stoul(conf["invadersVelocity"]));
    SI.invadersMaxVelocity = unsigned(stoul(conf["invadersMaxVelocity"]));
    SI.invadersVelocityStep = unsigned(stoul(conf["invadersVelocityStep"]));

    SI.shot = chrono::duration<int, milli>(stoi(conf["shot"]));
    SI.lastShot = chrono::steady_clock::now();

    SI.invadersShot = chrono::duration<int, milli>(stoi(conf["invadersShot"]));
    SI.invadersLastShot = chrono::steady_clock::now();

    SI.bonusInvaders = chrono::duration<int, milli>(stoi(conf["bonusInvaders"]));
    SI.LastBonusInvader = chrono::steady_clock::now();

    SI.bonusInvaderPos = pos(unsigned(stoul(conf["bonusInvaderPosAbs"])), unsigned(stoul(conf["bonusInvaderPosOrd"])));
    SI.playerPos = pos(unsigned(stoul(conf["playerPosAbs"])), unsigned(stoul(conf["playerPosOrd"]))); //placement intial joueur
    SI.lives = unsigned(stoul(conf["lives"]));
    SI.score = unsigned(stoul(conf["score"]));
    SI.bestScore = unsigned(stoul(conf["bestScore"]));
    SI.scoreForMissileDestruction = unsigned(stoul(conf["scoreForMissileDestruction"]));
    SI.scoreStep = unsigned(stoul(conf["scoreStep"]));
    SI.scoreStepBonusInvaders = unsigned(stoul(conf["scoreStepBonusInvaders"]));
    SI.torpedoVelocity = unsigned(stoul(conf["torpedoVelocity"]));
    SI.wave = unsigned(stoul(conf["wave"]));
}

///
/// \brief display a figure at each position contained in a vector of positions
/// \param window : the window on which the pictures are printed
/// \param positions : the vector of positions where the picture must be displayed
/// \param fig : the figure to be displayed
///
///
void display(minGL &window, const vector<pos> &positions, const figure &fig)
{
    for (vector<pos>::const_iterator it(positions.begin()); it != positions.end(); ++it)
        window << fig + *it;
}

///
/// \brief display the torpedos, the ennemies and the player on the screen
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

    window << SI.player.entityFig + SI.playerPos;
}

///
/// \brief display the spaces which will be filled with text on the screen
/// \param window : the window on which the HUD will be printed
/// \param SI : The strcut containing all the useful variables (including the picture of the player, used to show the lifes remaining)
///

void displayHUD(minGL &window, const spaceInvaders &SI)
{
    window << rectangle(pos(0, window.getWindowHeight()), pos(window.getWindowWidth() - 1, window.getWindowHeight() - 70), KGreen, KBlack);
    window << rectangle(pos(0, 0), pos(window.getWindowWidth() - 1, 50), KGreen, KBlack);
    window << SI.player.entityFig * 0.5 + pos(10, 8);
}

///
/// \brief display text to show the score, the lives remaining, the wave number and the number of invaders remaining on the screen
/// \param window : the window on which the texte will be printed
/// \param SI : the struct containing all the useful variables (including the wave number, the score, the lives remaining and the number of invaders alive)
///

void fillHUD(minGL &window, const spaceInvaders &SI)
{
    window.displayText(75, 12, to_string(SI.lives));

    window.displayText(5, window.getWindowHeight() - 40, "Score : ");
    window.displayText(80, window.getWindowHeight() - 40, to_string(SI.score));

    window.displayText(window.getWindowWidth() / 2 - 40, window.getWindowHeight() - 40, "Vague : ");
    window.displayText(window.getWindowWidth() / 2 + 30, window.getWindowHeight() - 40, to_string(SI.wave));

    window.displayText(window.getWindowWidth() - 130, window.getWindowHeight() - 40, "Invaders : ");
    window.displayText(window.getWindowWidth() - 25, window.getWindowHeight() - 40, to_string(SI.invadersPos.size()));
}

///
/// \brief Test if two entities collide
/// \param entity1 : the position of the first entity
/// \param entity2 : the position of the second entity
/// \param height1 : the height of the first entity
/// \param height2 : the height of the second entity
/// \param width1 : the width of the first entity
/// \param width2 : the width of the second entity
/// \return return true if the entities collide, else returns false
///

bool collisions(pos &entity1,
                pos &entity2,
                const unsigned &height1,
                const unsigned &height2,
                const unsigned &width1,
                const unsigned &width2)
{
    if (entity1.getOrd() + height1 >= entity2.getOrd() && entity1.getOrd() + height1 <= entity2.getOrd() + height2)
        if (entity1.getAbs() + width1 >= entity2.getAbs() && entity1.getAbs() <= entity2.getAbs() + width2)
            return true;

    return false;
}

///
/// \brief Updates the informations like the positions of the torpedoes, the lifes remaining if the player gets hit by a torpedo,
///     kills the invaders touched by a player's torpedo, removes the torpedoes if they leave the screen, moves the invaders (including the bonus invader)
///     and make one of them choosen randomly shoot.
/// \param SI : the struct containing all the useful variables to be used and updated
/// \param height : window's height
/// \param width : window's width
/// \param iLoose : boolean which become true if the player lose its last life by being hit by an ennemy torpedo
/// \param iWin : boolean which become true if there is no invader remaining in the wave
///

void process(spaceInvaders &SI, const unsigned &height, const unsigned &width, bool &iLoose, bool &iWin)
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
                    collision = collisions(*it, *itInvadersPos, SI.playerTorpedo.entityHeight, 15, SI.playerTorpedo.entityWidth, 50);
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

                //collision avec un invader bonus
                if (!collision)
                {
                    if (!(SI.bonusInvaderPos == pos(0, 0)))
                    {
                        collision = collisions(*it, SI.bonusInvaderPos, 15, 75, 50, 160);
                        if (collision)
                        {
                            SI.playerTorpedoPos.erase(it);
                            SI.bonusInvaderPos = pos(0, 0);
                            SI.LastBonusInvader = chrono::steady_clock::now();
                            SI.score += SI.scoreStepBonusInvaders;
                        }
                    }
                }

                if (!collision)
                {
                    //collision avec un missile
                    for (vector<pos>::iterator itInvadersTorpedoPos(SI.invadersTorpedoPos.begin()); !collision && itInvadersTorpedoPos != SI.invadersTorpedoPos.end(); ++itInvadersTorpedoPos)
                    {
                        collision = collisions(*it, *itInvadersTorpedoPos, 15, 15, 15, 15);
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
                *it = pos(it->getAbs(), it->getOrd() - 1);                  //déplacement
                collision = collisions(*it, SI.playerPos, 15, 55, 15, 110); //collision avec le joueur
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

        //ajouter invader bonus
        now = chrono::steady_clock::now();
        diff = now - SI.LastBonusInvader;
        if (diff >= SI.bonusInvaders && SI.bonusInvaderPos == pos(0, 0))
            SI.bonusInvaderPos = pos(10, height - 70);

        //deplacer invader bonus
        if (!(SI.bonusInvaderPos == pos(0, 0)))
        {
            if (SI.bonusInvaderPos.getAbs() == 10)
            {
                SI.bonusInvaderPos = pos(10, SI.bonusInvaderPos.getOrd() - (SI.invadersVelocity * 5));
                if (SI.bonusInvaderPos.getOrd() + 140 < height)
                    SI.bonusInvaderPos = SI.bonusInvaderPos + pos(1, 0);
            }
            else if (SI.bonusInvaderPos.getAbs() + 160 + 10 < width)
            {
                SI.bonusInvaderPos = SI.bonusInvaderPos + pos(SI.invadersVelocity * 5, 0);
            }
            else
            {

                if (SI.bonusInvaderPos.getOrd() + (SI.invadersVelocity * 5) + 70 < height)
                    SI.bonusInvaderPos = SI.bonusInvaderPos + pos(0, SI.invadersVelocity * 5);
                else
                {
                    SI.bonusInvaderPos = pos(0, 0);
                    SI.LastBonusInvader = chrono::steady_clock::now();
                }
            }
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
    }
}

///
/// \brief Read the keyboard inputs and move the player accordingly
/// \param window : contains the inputs and the size of the window
/// \param SI : the struct containing all the useful variables (including the cooldown between shoots and the vector containing the player's torpedo)
/// \param pause : boolean which become true if the player press the escape button
///

void ReadKeyboard(minGL &window, spaceInvaders &SI, bool &pause)
{
    if (window.isPressed(KEY_RIGHT) && SI.playerPos.getAbs() + 120 < window.getWindowWidth())
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

///
/// \brief Display the menu screen and get the keyboard inputs to leave the pause screen if enter is pressed
/// \param SI : the struct containing all the useful variables (including the invader's picture and his score)
/// \param window : the window on which the menu screen will be printed
/// \param frameDuration : the time between each frame
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
        window.displayText(window.getWindowWidth() - 600, window.getWindowHeight() / 2, "Appuyez sur entree pour jouer, echap pour quitter");
        window.displayText(50, window.getWindowHeight() - 50, "Meilleur score : ");
        window.displayText(200, window.getWindowHeight() - 50, to_string(SI.bestScore));

        window.displayText(50, window.getWindowHeight() - 70, "Dernier score : ");
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

void SIpause(const spaceInvaders &SI, minGL &window, const chrono::duration<double, milli> frameDuration)
{
    keyType key(0, false);
    while (key == keyType(0, false))
    {
        chrono::time_point<chrono::steady_clock> beg(chrono::steady_clock::now());

        window.clearScreen();
        window << SI.player.entityFig * 2 + pos(100, 0);
        window.updateGraphic();
        window.displayText(window.getWindowWidth() - 600, window.getWindowHeight() / 2, "Appuyez sur entree pour continuer");
        window.displayText(50, window.getWindowHeight() - 50, "Meilleur score : ");
        window.displayText(200, window.getWindowHeight() - 50, to_string(SI.bestScore));

        window.displayText(50, window.getWindowHeight() - 70, "Score : ");
        window.displayText(200, window.getWindowHeight() - 70, to_string(SI.score));

        if (window.isPressed(KEY_ENTER))
            key = KEY_ENTER;

        chrono::time_point<chrono::steady_clock> end(chrono::steady_clock::now());
        chrono::duration<double, milli> diff(end - beg);
        if (diff < frameDuration)
            this_thread::sleep_for(frameDuration - diff);
    }
}

///
/// \brief The main function of the game, which use the others to display the screen, get inputs ... and which manage the pause menu, the framerate,
///     the success and defeat, the generation of the new waves, manage the highscore
/// \param window : the window on which everything will be displayed
///

void mainSpaceInvaders(minGL &window)
{

    spaceInvaders SI, SIBase; //SI est utilisé pour le jeu et SIBase conserve les valeurs données par la fonction init sauf pour les scores
    initSpaceInvaders(SI);
    invadersGeneration(SI, window.getWindowHeight(), window.getWindowWidth());
    SIBase = SI;

    const chrono::duration<double, milli> frameDuration(33.3); //30fps

    while (SpaceInvadersMenu(SIBase, window, frameDuration) != KEY_ESCAPE)
    {
        bool iLoose(false), iWin(false), pause(false);
        SI.LastBonusInvader = chrono::steady_clock::now(); //pour éviter un invader bonus a chaque debut de partie

        while (!iLoose)
        {
            if (pause)
            {
                SIpause(SI, window, frameDuration);
                SI.LastBonusInvader = chrono::steady_clock::now(); //pour éviter un invader bonus a chaque sortie de pause
                pause = false;
            }

            chrono::time_point<chrono::steady_clock> beg(chrono::steady_clock::now());

            process(SI, window.getWindowHeight(), window.getWindowWidth(), iLoose, iWin);
            ReadKeyboard(window, SI, pause);

            if (iWin)
            {
                iWin = false;
                unsigned wave = SI.wave;
                SI = SIBase;
                SI.wave = wave + 1;
                SI.LastBonusInvader = chrono::steady_clock::now(); //pour éviter un invader bonus a chaque nouvelle vague
                window.displayText(window.getWindowWidth() / 2 - 60, window.getWindowHeight() / 2, "vague suivante...");
                window.updateGraphic();
                this_thread::sleep_for(chrono::duration<int, milli>(1000));
            }
            else
                SIBase.score = SI.score;

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

        if (SIBase.bestScore < SI.score)
            SIBase.bestScore = SI.score;
        SI = SIBase;
        SI.score = 0;
    }
}

///
/// \brief Initialize Glut and MinGl, creates a seed for randomness and launches the game.
/// \return
///

int main()
{
    minGL window(1280, 720, "Space Invader", KBlack);
    window.initGlut();
    window.initGraphic();

    srand(time(NULL));
    mainSpaceInvaders(window);

    return 0;
}
