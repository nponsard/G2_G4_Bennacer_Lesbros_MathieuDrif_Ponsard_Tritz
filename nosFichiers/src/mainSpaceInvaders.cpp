#include "mainSpaceInvaders.h"
#include "utils/display.h"
#include "utils/music.h"
#include "utils/keyboardInput.h"

#include "utils/scoresort.h"
#include "utils/savescores.h"

#include <thread>

using namespace std;

///
/// \brief The main function of the game, which use the others to display the screen, get inputs ... and which manage the pause menu, the framerate,
///     the success and defeat, the generation of the new waves, manage the highscore
/// \param window : the window on which everything will be displayed
///

void mainSI(minGL &window)
{
    bool playmusic(true);
    //https://downloads.khinsider.com/game-soundtracks/album/space-invaders-91-sega-genesis
    spaceInvaders SI, SIBase; //SI est utilisé pour le jeu et SIBase conserve les valeurs données par la fonction init sauf pour les scores
    initSpaceInvaders(SI);
    startMusic();
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

            SIBase.score = SI.score;

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
                window.displayText(window.getWindowWidth() / 2 - 60, window.getWindowHeight() / 2, "Next wave...");
                window.updateGraphic();
                this_thread::sleep_for(chrono::duration<int, milli>(1000));
            }

            window.clearScreen();
            displaySpace(window, SI);
            displayHUD(window, SI);
            window.updateGraphic();
            fillHUD(window, SI);

            if (pause)
            {
                window.resetKey(KEY_ESCAPE); // éviter répétition de touches
                SIpause(SI, window, frameDuration, iLoose, playmusic);
                SI.LastBonusInvader = chrono::steady_clock::now(); //pour éviter un invader bonus a chaque sortie de pause
                pause = false;
            }

            chrono::time_point<chrono::steady_clock> end(chrono::steady_clock::now());
            chrono::duration<double, milli> diff(end - beg);
            if (diff < frameDuration)
                this_thread::sleep_for(frameDuration - diff);
        }
        system("aplay -q '../nosFichiers/ressources/gameOver.wav' &");

        SI = SIBase;
        SI.score = 0;

        //update bestScores vector
        if (SIBase.bestScores.size() < 3)
        {
            string name(ReadName(window, frameDuration));
            insertScore(SIBase.bestScores, name, SIBase.score);
            saveScores(SIBase.bestScores, "scores.yaml");
        }
        else if (SIBase.bestScores[SIBase.bestScores.size() - 1].second < SIBase.score)
        {
            string name(ReadName(window, frameDuration));
            insertScore(SIBase.bestScores, name, SIBase.score);
            SIBase.bestScores.pop_back();
            saveScores(SIBase.bestScores, "scores.yaml");
        }
    }
}

///
/// \brief Updates the informations like the positions of the torpedoes, the lifes remaining if the player gets hit by a torpedo,
///     kills the invaders touched by a player's torpedo, removes the torpedoes if they leave the screen, moves the invaders (including the bonus invader)
///     and make one of them choosen randomly shoot.
/// \param SI : struct containing all the useful variables to be used and updated
/// \param height : window's height
/// \param width : windSI.invadersPos.size()ow's width
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

                        if (itInvadersPos->second == 1)
                        {
                            if (rand() % max(unsigned(4), (10 - SI.wave / 5)) == 0) //generation bonus
                            {
                                std::pair<pos, short> upgrade;
                                upgrade.first = itInvadersPos->first + pos(SI.invaders.entityWidth / 2, SI.invaders.entityHeight / 2) + pos(-15, -15);
                                upgrade.second = rand() % SI.upgrades.entityFigs.size();
                                SI.UpgradePos.push_back(upgrade);
                            }
                            SI.invadersPos.erase(itInvadersPos);
                            system("aplay -q '../nosFichiers/ressources/invadersDeath.wav' &");
                            SI.score += SI.scoreStep;
                            SI.scoreStep += 20;

                            if (SI.invadersPos.size() != 0)
                                SI.invadersVelocity = min(unsigned(SI.invadersMinVelocity + ((SI.invadersMaxVelocity - SI.invadersMinVelocity) * 3 / SI.invadersPos.size())), SI.invadersMaxVelocity);
                        }
                        else
                        {
                            --itInvadersPos->second;
                            system("aplay -q '../nosFichiers/ressources/invadersHit.wav' &");
                        }
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
                            upgrade.second = rand() % SI.upgrades.entityFigs.size();
                            SI.UpgradePos.push_back(upgrade);
                            SI.playerTorpedoPos.erase(it);
                            system("aplay -q '../nosFichiers/ressources/bonusInvaderDeath.wav' &");
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
                    else
                        system("aplay -q '../nosFichiers/ressources/loseLife.wav' &");
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
                collision = collisions(itupgrade->first, SI.playerPos, SI.upgrades.entityHeight, SI.player.entityHeight, SI.upgrades.entityWidth, SI.player.entityWidth); //collision avec le joueur, on utilise lifeUpgrade pour la collision de base
                if (collision)
                {
                    if (itupgrade->second == 0)
                        ++SI.lives;
                    if (itupgrade->second == 1)
                        SI.shot -= SI.shot / 10;
                    if (itupgrade->second == 2)
                        SI.score += SI.wave * 100;
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
            vector<pair<pos, unsigned>>::iterator itInvaders(SI.invadersPos.begin() + (rand() % SI.invadersPos.size())); //choix d'un invader
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

        //déplacement

        //deplacer invader bonus
        if (!(SI.bonusInvaderPos == pos(0, 0)))
        {
            if (SI.bonusInvaderPos.getAbs() == 10) //descente
            {
                SI.bonusInvaderPos = pos(10, SI.bonusInvaderPos.getOrd() - (SI.invadersVelocity * SI.bonusInvaderVelocityFactor));
                if (SI.bonusInvaderPos.getOrd() + 150 < height)
                    SI.bonusInvaderPos = SI.bonusInvaderPos + pos(1, 0);
            }
            else if (SI.bonusInvaderPos.getAbs() + SI.bonusInvader.entityWidth + (SI.invadersVelocity * SI.bonusInvaderVelocityFactor) < width)
            {
                SI.bonusInvaderPos = SI.bonusInvaderPos + pos(SI.invadersVelocity * SI.bonusInvaderVelocityFactor, 0);
            }
            else
            {

                if (SI.bonusInvaderPos.getOrd() + (SI.invadersVelocity * SI.bonusInvaderVelocityFactor) + SI.bonusInvader.entityHeight < height)
                    SI.bonusInvaderPos = SI.bonusInvaderPos + pos(0, SI.invadersVelocity * SI.bonusInvaderVelocityFactor);
                else
                {
                    SI.bonusInvaderPos = pos(0, 0);
                    SI.LastBonusInvader = chrono::steady_clock::now();
                }
            }
        }

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
