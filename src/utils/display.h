#ifndef DISPLAY_H
#define DISPLAY_H

#include "minGL/graph/mingl.h"
#include "spaceinvaders.h"


void display(minGL &window, const std::vector<pos> &positions, const figure &fig);
void display(minGL &window, const std::vector<std::pair<pos, short>> &upgrades, const std::vector<figure> &figures);
void display(minGL &window, const std::vector<std::pair<pos, unsigned>> &positions, const figure &fig);
void displaySpace(minGL &window, const spaceInvaders &SI);
void displayHUD(minGL &window, const spaceInvaders &SI);
void fillHUD(minGL &window, const spaceInvaders &SI);
keyType SpaceInvadersMenu(const spaceInvaders &SI, minGL &window, const std::chrono::duration<double, std::milli> frameDuration);
void SIpause(const spaceInvaders &SI, minGL &window, const std::chrono::duration<double, std::milli> frameDuration, bool &iLoose, bool &playmusic);
std::string ReadName(minGL &window, const std::chrono::duration<double, std::milli> frameDuration, const unsigned &nbCharMax = 3);



#endif // DISPLAY_H
