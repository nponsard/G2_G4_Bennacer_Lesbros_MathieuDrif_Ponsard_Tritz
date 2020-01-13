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
#include <utility>

#include "utils/spaceinvaders.h"
#include "utils/loadconfig.h"
#include "utils/loadScores.h"
#include "utils/scoresort.h"
#include "utils/savescores.h"

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

//http://mperriss.free.fr/opengl/Guide_2D/claviersouris.htm
const keyType KEY_UP({101, true});
const keyType KEY_DOWN({103, true});
const keyType KEY_LEFT({100, true});
const keyType KEY_RIGHT({102, true});
const keyType KEY_ESCAPE({27, false});
const keyType KEY_SPACE({32, false});
const keyType KEY_ENTER({13, false});
const keyType KEY_RETURN({8, false});

///
/// \brief Add invaders to the vector containing their pos until they fill their starting space
/// \param SI : the struct containing all useful variables (including the size of the invaders and a vector containing all invaders' positions)
/// \param height : the height of the space to fill with invaders
/// \param width : the width of the space to fill with invaders
///

void invadersGeneration(spaceInvaders &SI, const unsigned &height, const unsigned &width)
{
    SI.invadersPos.clear();
    unsigned Xshift, Yshift(55);
    for (unsigned i(0); i < (SI.wave-1) % 4 + 1 ; ++i)
    {
        Xshift = 0;
        while (Xshift + SI.invaders.entityWidth + (2 * SI.invaders.entityWidth) /*marge min*/ < width)
        {
            SI.invadersPos.push_back(make_pair(pos(Xshift, height - 200 - (Yshift * i)), (SI.wave-1) / 4 + 1));
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
    SI.bestScores = loadScores("scores.yaml");

    SI.invadersVelocity = unsigned(stoul(conf["invadersVelocity"]));
    SI.invadersMaxVelocity = unsigned(stoul(conf["invadersMaxVelocity"]));
    SI.invadersVelocityStep = unsigned(stoul(conf["invadersVelocityStep"]));
    SI.upgradeVelocity = unsigned(stoul(conf["upgradeVelocity"]));

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


void display(minGL &window, const vector<pair<pos, short>> &upgrades, const vector<figure> &figures)
{
    for (vector<pair<pos, short>>::const_iterator it(upgrades.begin()); it != upgrades.end(); ++it)
        window << figures[it->second] + it->first;
}

void display(minGL &window, const vector<pair<pos, unsigned>> &positions, const figure &fig)
{
    for (vector<pair<pos, unsigned>>::const_iterator it(positions.begin()); it != positions.end(); ++it)
        window << fig + it->first;
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
    display(window, SI.UpgradePos, SI.upgradeTypes);

    window << SI.player.entityFig + SI.playerPos;
}

///
/// \brief display the spaces which will be filled with text on the screen
/// \param window : the window on which the HUD will be printed
/// \param SI : The struct containing all the useful variables (including the picture of the player, used to show the lifes remaining)
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
            if (it->getOrd() + 1 + SI.playerTorpedo.entityHeight < height)
            {
                *it = *it + pos(0, 1); //déplacement

                //collision avec un invader
                for (vector<pair<pos, unsigned>>::iterator itInvadersPos(SI.invadersPos.begin()); !collision && itInvadersPos != SI.invadersPos.end(); ++itInvadersPos)
                {
                    collision = collisions(*it, itInvadersPos->first, SI.playerTorpedo.entityHeight, SI.invaders.entityHeight, SI.playerTorpedo.entityWidth, SI.invaders.entityWidth);
                    if (collision)
                    {
                        SI.playerTorpedoPos.erase(it);
                        if (rand() % max(unsigned(4), (10 - SI.wave / 5)) == 0)//generation bonus
                        {
                            std::pair<pos, short> upgrade;
                            upgrade.first = itInvadersPos->first + pos(SI.invaders.entityWidth / 2, SI.invaders.entityHeight / 2) + pos(-15, -15);
                            upgrade.second = rand() % SI.upgradeTypes.size();
                            SI.UpgradePos.push_back(upgrade);
                        }
                        if(itInvadersPos->second == 1)
                        {
                            SI.invadersPos.erase(itInvadersPos);
                            SI.score += SI.scoreStep;
                            SI.scoreStep += 20;
                        }
                        else
                            --itInvadersPos->second;
                        system("aplay '../ressources/laser.wav' &");
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
                        collision = collisions(*it, SI.bonusInvaderPos, SI.playerTorpedo.entityHeight, SI.bonusInvader.entityHeight, SI.playerTorpedo.entityWidth, SI.bonusInvader.entityWidth);
                        if (collision)
                        {
                            std::pair<pos, short> upgrade;
                            upgrade.first = SI.bonusInvaderPos + pos(SI.bonusInvader.entityWidth / 2, SI.bonusInvader.entityHeight / 2) + pos(-15, -15);
                            upgrade.second = rand() % SI.upgradeTypes.size();
                            SI.UpgradePos.push_back(upgrade);
                            SI.playerTorpedoPos.erase(it);
                            system("aplay '../ressources/laser.wav' &");
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
                        collision = collisions(*it, *itInvadersTorpedoPos, SI.playerTorpedo.entityHeight, SI.invadersTorpedo.entityHeight, SI.playerTorpedo.entityWidth, SI.invadersTorpedo.entityWidth);
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
                *it = pos(it->getAbs(), it->getOrd() - 1);                                                                                                                 //déplacement
                collision = collisions(*it, SI.playerPos, SI.invadersTorpedo.entityHeight, SI.player.entityHeight, SI.invadersTorpedo.entityWidth, SI.player.entityWidth); //collision avec le joueur
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

    //deplacement des bonus
    vector<std::pair<pos, short>>::iterator itupgrade = SI.UpgradePos.begin();
    while (itupgrade != SI.UpgradePos.end())
    {
        bool collision(false);
        for (unsigned tempMove(0); !collision && tempMove < SI.upgradeVelocity; ++tempMove) //deplacer par pas de 1 pour verifier collisions meme quand vitesse élevée
        {
            if (itupgrade->first.getOrd() > 1)
            {
                itupgrade->first = pos(itupgrade->first.getAbs(), itupgrade->first.getOrd() - 1);                                                                               //déplacement
                collision = collisions(itupgrade->first, SI.playerPos, SI.lifeUpgrade.entityHeight, SI.player.entityHeight, SI.lifeUpgrade.entityWidth, SI.player.entityWidth); //collision avec le joueur, on utilise lifeUpgrade pour la collision de base
                if (collision)
                {
                    if (itupgrade->second == 0)
                        ++SI.lives;
                    if (itupgrade->second == 1)
                        SI.shot -= SI.shot / 10;
                    if (itupgrade->second == 2)
                        SI.score += 10 + SI.wave * 10;
                    SI.UpgradePos.erase(itupgrade);
                }
            }
            else //collision avec le mur
            {
                SI.UpgradePos.erase(itupgrade);
                collision = true;
            }
        }
        if (!collision)
            ++itupgrade;
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
            vector<pair<pos, unsigned>>::iterator itInvaders(SI.invadersPos.begin()
                                                             + (rand() % SI.invadersPos.size()));//choix d'un invader
            //trouver l'invader le plus bas dans cette colonne
            for (vector<pair<pos, unsigned>>::iterator it2(SI.invadersPos.begin()); it2 != SI.invadersPos.end(); ++it2)
                if (it2->first.getAbs() == itInvaders->first.getAbs() && it2->first.getOrd() < itInvaders->first.getOrd())
                    itInvaders = it2;

            SI.invadersTorpedoPos.push_back(pos(itInvaders->first.getAbs() + 27, itInvaders->first.getOrd()));

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
        vector<pair<pos, unsigned>>::iterator extremum(SI.invadersPos.begin());

        if (SI.InvadersRight)
        {
            for (vector<pair<pos, unsigned>>::iterator it2(extremum + 1); it2 != SI.invadersPos.end(); ++it2)
                if (it2->first.getAbs() > extremum->first.getAbs())
                    extremum = it2;

            if (extremum->first.getAbs() + SI.invadersVelocity + SI.invaders.entityWidth < width)
            {
                //deplacer tous les invaders
                vector<pair<pos, unsigned>>::iterator itInvaders(SI.invadersPos.begin());
                while (itInvaders != SI.invadersPos.end())
                {
                    itInvaders->first = pos(itInvaders->first.getAbs() + SI.invadersVelocity, itInvaders->first.getOrd());
                    ++itInvaders;
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
            for (vector<pair<pos, unsigned>>::iterator it2(SI.invadersPos.begin() + 1); it2 != SI.invadersPos.end(); ++it2)
                if (it2->first.getAbs() < extremum->first.getAbs())
                    extremum = it2;

            if (extremum->first.getAbs() > SI.invadersVelocity)
            {
                //deplacer tous les invaders
                vector<pair<pos, unsigned>>::iterator itInvaders(SI.invadersPos.begin());
                while (itInvaders != SI.invadersPos.end())
                {
                    itInvaders->first = pos(itInvaders->first.getAbs() - SI.invadersVelocity, itInvaders->first.getOrd());
                    ++itInvaders;
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
            for (vector<pair<pos, unsigned>>::iterator it2(SI.invadersPos.begin() + 1); it2 != SI.invadersPos.end(); ++it2)
                if (it2->first.getOrd() < extremum->first.getOrd())
                    extremum = it2;

            if (extremum->first.getOrd() > SI.invaders.entityHeight + 50 /*score height*/ + SI.player.entityHeight)
            {
                //deplacer tous les invaders
                vector<pair<pos, unsigned>>::iterator itInvaders(SI.invadersPos.begin());
                while (itInvaders != SI.invadersPos.end())
                {
                    itInvaders->first = pos(itInvaders->first.getAbs(), itInvaders->first.getOrd() - 30);
                    ++itInvaders;
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

        window.displayText(window.getWindowWidth() - 420, window.getWindowHeight() / 2 + 260, "Meilleurs scores : ");

        for (unsigned i(0); i < SI.bestScores.size() && i < 3; ++i)
        {
            window.displayText(window.getWindowWidth() - 400, window.getWindowHeight() / 2 + 220 - (25 * i), SI.bestScores[i].first);
            window.displayText(window.getWindowWidth() - 370, window.getWindowHeight() / 2 + 220 - (25 * i), ":");
            window.displayText(window.getWindowWidth() - 350, window.getWindowHeight() / 2 + 220 - (25 * i), to_string(SI.bestScores[i].second));
        }

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

void SIpause(const spaceInvaders &SI, minGL &window, const chrono::duration<double, milli> frameDuration, bool &iLoose)
{
    keyType key(0, false);
    while (key == keyType(0, false) && !iLoose)
    {
        chrono::time_point<chrono::steady_clock> beg(chrono::steady_clock::now());

        window.clearScreen();
        window << SI.player.entityFig * 2 + pos(100, 0);
        window.updateGraphic();
        window.displayText(window.getWindowWidth() - 600, window.getWindowHeight() / 2, "Appuyez sur ENTREE pour continuer");
        window.displayText(window.getWindowWidth() - 600, window.getWindowHeight() / 2 - 20, "Appuyez sur ECHAP pour quitter la partie");
        window.displayText(50, window.getWindowHeight() - 50, "Meilleur score : ");
        window.displayText(200, window.getWindowHeight() - 50, to_string(SI.bestScore));

        window.displayText(50, window.getWindowHeight() - 70, "Score : ");
        window.displayText(200, window.getWindowHeight() - 70, to_string(SI.score));

        if (window.isPressed(KEY_ENTER))
            key = KEY_ENTER;

        if (window.isPressed(KEY_ESCAPE))
        {
            iLoose = true;
            this_thread::sleep_for(chrono::duration<int, milli>(50)); //delai pour éviter répétition de touches
        }

        chrono::time_point<chrono::steady_clock> end(chrono::steady_clock::now());
        chrono::duration<double, milli> diff(end - beg);
        if (diff < frameDuration)
            this_thread::sleep_for(frameDuration - diff);
    }
}

string ReadName(minGL &window, const chrono::duration<double, milli> frameDuration, const unsigned &nbCharMax = 3)
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

        window.displayText(window.getWindowWidth() / 2 - 150, window.getWindowHeight() / 2 + 100, "Nouveau meilleur score, entrez votre nom");

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
                    this_thread::sleep_for(chrono::duration<int, milli>(50)); //delai pour éviter répétition de touches
                }
            }
        }
        if (window.isPressed(KEY_RETURN))
            if (name.size() != 0)
            {
                name.pop_back();
                this_thread::sleep_for(chrono::duration<int, milli>(50)); //delai pour éviter répétition de touches
            }

        if (window.isPressed(KEY_ENTER))
        {
            key = KEY_ENTER;
            this_thread::sleep_for(chrono::duration<int, milli>(50)); //delai pour éviter répétition de touches
        }

        chrono::time_point<chrono::steady_clock> end(chrono::steady_clock::now());
        chrono::duration<double, milli> diff(end - beg);
        if (diff < frameDuration)
            this_thread::sleep_for(frameDuration - diff);
    }
    window.resetKey(KEY_ENTER); //éviter répétition de touches en arrivant au menu
    return name;
}

///
/// \brief The main function of the game, which use the others to display the screen, get inputs ... and which manage the pause menu, the framerate,
///     the success and defeat, the generation of the new waves, manage the highscore
/// \param window : the window on which everything will be displayed
///

void mainSpaceInvaders(minGL &window)
{
    //https://downloads.khinsider.com/game-soundtracks/album/space-invaders-91-sega-genesis
    system("bash ../ressources/audioSpaceInvaders.bash &");
    spaceInvaders SI, SIBase; //SI est utilisé pour le jeu et SIBase conserve les valeurs données par la fonction init sauf pour les scores
    initSpaceInvaders(SI);
    SI.wave = 9;

    invadersGeneration(SI, window.getWindowHeight(), window.getWindowWidth());
    SIBase = SI;
    const chrono::duration<double, milli> frameDuration(33.3); //30fps

    while (SpaceInvadersMenu(SIBase, window, frameDuration) != KEY_ESCAPE)
    {
        bool iLoose(false), iWin(false), pause(false);
        SI.LastBonusInvader = chrono::steady_clock::now(); //pour éviter un invader bonus a chaque debut de partie

        while (!iLoose)
        {
            chrono::time_point<chrono::steady_clock> beg(chrono::steady_clock::now());

            process(SI, window.getWindowHeight(), window.getWindowWidth(), iLoose, iWin);
            ReadKeyboard(window, SI, pause);

            if (iWin)
            {
                iWin = false;
                unsigned wave = SI.wave;
                unsigned lives = SI.lives;
                SI = SIBase;
                SI.lives = lives;
                SI.wave = wave + 1;
                SI.LastBonusInvader = chrono::steady_clock::now(); //pour éviter un invader bonus a chaque nouvelle vague
                invadersGeneration(SI, window.getWindowHeight(), window.getWindowWidth());
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

            if (pause)
            {
                this_thread::sleep_for(chrono::duration<int, milli>(50)); //delai pour éviter répétition de touches
                SIpause(SI, window, frameDuration, iLoose);
                SI.LastBonusInvader = chrono::steady_clock::now(); //pour éviter un invader bonus a chaque sortie de pause
                pause = false;
            }

            chrono::time_point<chrono::steady_clock> end(chrono::steady_clock::now());
            chrono::duration<double, milli> diff(end - beg);
            if (diff < frameDuration)
                this_thread::sleep_for(frameDuration - diff);
        }

        if (SIBase.bestScore < SI.score)
            SIBase.bestScore = SI.score;
        SI = SIBase;
        SI.score = 0;

        //update bestScores vector
        if (SIBase.bestScores.size() < 3)
        {
            string name(ReadName(window, frameDuration));
            SIBase.bestScores.push_back(make_pair(name, SIBase.score));
            scoreSort(SIBase.bestScores);
            saveScores(SIBase.bestScores, "scores.yaml");
        }
        else if (SIBase.bestScores[SIBase.bestScores.size() - 1].second < SIBase.score)
        {
            string name(ReadName(window, frameDuration));
            SIBase.bestScores.push_back(make_pair(name, SIBase.score));
            scoreSort(SIBase.bestScores);
            SIBase.bestScores.pop_back();
            saveScores(SIBase.bestScores, "scores.yaml");
        }
    }
}

void killMusic()
{
    system("pkill -f 'bash ../ressources/audioSpaceInvaders.bash'");
    system("pkill -f 'aplay ../ressources/theme.wav'");
}


///
/// \brief Initialize Glut and MinGl, creates a seed for randomness and launches the game.
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
    mainSpaceInvaders(window);

    return 0;
}
