#ifndef KEYBOARDINPUT_H
#define KEYBOARDINPUT_H

#include "nosFichiers/src/minGL/graph/mingl.h"
#include "spaceinvaders.h"

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

void ReadKeyboard(minGL &window, spaceInvaders &SI, bool &pause);


#endif // KEYBOARDINPUT_H
