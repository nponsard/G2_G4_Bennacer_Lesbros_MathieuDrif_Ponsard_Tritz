#include "music.h"
#include "cstdlib"

///
/// \brief starts the music
///

void startMusic()
{
    system("bash ../nosFichiers/ressources/audioSpaceInvaders.bash &");
}

///
/// \brief stops the music
///

void killMusic()
{
    system("pkill -f 'bash ../nosFichiers/ressources/audioSpaceInvaders.bash'");
    system("pkill -f 'aplay -q ../nosFichiers/ressources/theme.wav'");
}

