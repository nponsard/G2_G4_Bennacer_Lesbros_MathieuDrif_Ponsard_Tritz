#include "stdlib.h"
#include "utils/music.h"

void startMusic()
{
    system("bash ../ressources/audioSpaceInvaders.bash &");
}
void killMusic()
{
    system("pkill -f 'bash ../ressources/audioSpaceInvaders.bash'");
    system("pkill -f 'aplay -q ../ressources/theme.wav'");
}