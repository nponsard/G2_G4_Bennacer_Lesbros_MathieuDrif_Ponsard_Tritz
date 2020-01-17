#include "stdlib.h"
#include "utils/music.h"

///
/// \brief starts the music
///

void startMusic()
{
    system("bash ../ressources/audioSpaceInvaders.bash &");
}

///
/// \brief stops the music
///

void killMusic()
{
    system("pkill -f 'bash ../ressources/audioSpaceInvaders.bash'");
    system("pkill -f 'aplay -q ../ressources/theme.wav'");
}

