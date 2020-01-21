#include "music.h"
#include "cstdlib"

///
/// \brief starts the music
///

void startMusic()
{
    system("bash ../G2_G4_Bennacer_Lesbros_MathieuDrif_Ponsard_Tritz/nosFichiers/ressources/audioSpaceInvaders.bash &");
}

///
/// \brief stops the music
///

void killMusic()
{
    system("pkill -f 'bash ../G2_G4_Bennacer_Lesbros_MathieuDrif_Ponsard_Tritz/nosFichiers/ressources/audioSpaceInvaders.bash'");
    system("pkill -f 'aplay -q ../G2_G4_Bennacer_Lesbros_MathieuDrif_Ponsard_Tritz/nosFichiers/ressources/theme.wav'");
}
