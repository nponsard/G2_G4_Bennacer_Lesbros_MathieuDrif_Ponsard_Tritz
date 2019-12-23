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
 * \brief The minGL class
 *          sert de classe de base à tout le bordel
 *
 */

//pour les fonts et l'affichage des string voir : https://www.opengl.org/resources/libraries/glut/spec3/node76.html
typedef std::pair<int, bool> keyType; // clef, spécial
typedef std::map<keyType, bool> keyMap;
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
    keyMap keyboardMap;

public:
    static void initGlut()
    {
        int tmp = 0;
        glutInit(&tmp, NULL);
    }
    void initGraphic();
    void stopGaphic();

    bool isPressed(keyType key);
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
