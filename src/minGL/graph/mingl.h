#ifndef MINGL_H
#define MINGL_H

#include <string>
#include <vector>
#include <queue>
#include <memory> //shared_ptr

#include "freeglut.h"

#include "libgraphique_fonts.h"
#include "rgbcolor.h"

#include "../tools/myexception.h"
#include "../figs/pos.h"

#include "../tools/pixelexception.h"

/*!
 * \brief keyType : custom type representing a key of the keyboard 
 * \details It's a pair of int and bool <br>
 *          <ul><li> the int is for the keycode </li>
 *              <li> the bool indicates if it's special or not (true -> special, false-> not special)</li></ul>
 * 
 */
typedef std::pair<int, bool> keyType; // cle, spécial
/*!
 * 
 * \brief   keyMap : map of the pressed keys
 * \details The keys are \ref keyType and is linked to true if pressed and false if not pressed (or reset)
 * 
 */
typedef std::map<keyType, bool> keyMap;

/*!
 * \brief minGL class: 
 *        the entry point to draw thing on the screen
 *
 */

//pour les fonts et l'affichage des string voir : https://www.opengl.org/resources/libraries/glut/spec3/node76.html
class minGL
{
private:
    //les données membres en tant que tel
    const unsigned windowWidth;
    const unsigned windowHeight;
    const std::string windowName;
    std::shared_ptr<font> windowFont = std::make_shared<font>(FONT_HELVETICA_10);
    RGBcolor fontColor = KBlack;
    unsigned fontSize = 10;
    RGBcolor bgColor;
    keyMap keyboardMap;

    //ce dont on a besoin pour glut
    short glutWindowId = 0;
    std::vector<GLubyte> screenBuffer;

    //les handlers
    void callReshape(int h, int w);
    void callDisplay();
    void callKeyboard(unsigned char key, int x = 0, int y = 0);
    void callKeyboardUp(unsigned char key, int x = 0, int y = 0);
    void callKeyboardSpecial(int key, int x = 0, int y = 0);
    void callKeyboardUpSpecial(int key, int x = 0, int y = 0);

public:
    static void initGlut()
    {
        int tmp = 0;
        glutInit(&tmp, NULL);
    }
    void initGraphic();
    void stopGaphic();

    bool isPressed(const keyType &key);
    void resetKey(const keyType &key);
    void displayText(const unsigned &x, const unsigned &y, const std::string &str);
    minGL(const unsigned &Width = 640, const unsigned &Height = 480, const std::string &Name = std::string(), const RGBcolor &backGroungColor = KWhite);
    ~minGL();
    void updateGraphic();
    void clearScreen() throw(myexception);
    void setPixel(const pos &pos_, const RGBcolor &col) throw(PixelException);

    void setBgColor(const RGBcolor &col);

    unsigned getWindowWidth() const;
    unsigned getWindowHeight() const;
};

#endif // MINGL_H
