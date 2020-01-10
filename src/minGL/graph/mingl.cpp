#include <map>

#include "mingl.h"

using namespace std;
using namespace nsUtil;

//astuce pour faire passer les handlers en fonction static dans initGraphic ()
namespace
{
map<int, minGL *> anyWindow;

template <typename T, T oHandler>
struct callBackBuilder;

template <typename Obj, typename... Arg, void (Obj::*oHandler)(Arg...)>
struct callBackBuilder<void (Obj::*)(Arg...), oHandler>
{
    static void callback(Arg... arg)
    {
        int current_id = glutGetWindow();
        //cout << "window [" << current_id << "] handler call" << endl;
        auto it = anyWindow.find(current_id);
        if (it != anyWindow.end())
        {
            (it->second->*oHandler)(arg...);
        }
    }
};
} // namespace

#define BIND_CALLBACK(HANDLER) callBackBuilder<decltype(HANDLER), HANDLER>::callback

minGL::minGL(const unsigned &Width, const unsigned &Height, const std::string &Name, const RGBcolor &backGroungColor) : windowWidth(Width),
                                                                                                                        windowHeight(Height),
                                                                                                                        windowName(Name),
                                                                                                                        bgColor(backGroungColor)
{
    screenBuffer.resize(Width * Height * 3);
    // initGlut();
    // initGraphic();
}

minGL::~minGL()
{
    auto it = anyWindow.find(glutWindowId);
    if (it != anyWindow.end())
        anyWindow.erase(it);
    stopGaphic();
}

void minGL::updateGraphic()
{
    glFlush();
    glutPostRedisplay();
    glutMainLoopEvent();
}

void minGL::clearScreen() throw(myexception)
{
    for (unsigned i(0); i < windowWidth; ++i)
        for (unsigned j(0); j < windowHeight; ++j)
            setPixel(pos(i, j), bgColor);
}

void minGL::setPixel(const pos &pos_, const RGBcolor &col) throw(PixelException)
{

    //if (pos_.abs > windowWidth) throw myexception (kErrTooRight);
    //if (pos_.ord > windowHeight) throw myexception (kErrTooHight);
    if (pos_.abs > windowWidth)
        throw PixelException(pos_, col, "Pixel too right");
    if (pos_.ord > windowHeight)
        throw PixelException(pos_, col, "Pixel too high");

    screenBuffer[3 * (pos_.ord * windowWidth + pos_.abs) + 0] = col.Red;
    screenBuffer[3 * (pos_.ord * windowWidth + pos_.abs) + 1] = col.Green;
    screenBuffer[3 * (pos_.ord * windowWidth + pos_.abs) + 2] = col.Blue;
}
/*
char minGL::get_key()
{
    glutMainLoopEvent();
    char key;
    while (keyboardBuffer.size() == 0)
    {
        glutMainLoopEvent();
    }
    key = keyboardBuffer.front();
    keyboardBuffer.pop();
    return (key);
}

std::map<char, bool> minGL::get_key_2()
{
    glutMainLoopEvent();
    return keyboardMap;
}*/

/*!
 *  \author     Nils Ponsard
 *  \brief      Change la couleur de remplacement lors de l'effacement, donc du fond d'écran  
 */
void minGL::setBgColor(const RGBcolor &col)
{
    bgColor = col;
}

//static void minGL::initGlut()
//{
//    int tmp=0;
//    glutInit(&tmp, NULL);

//}

void minGL::initGraphic()
{

    // Initialisation GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(int(windowWidth), int(windowHeight));
    glutInitWindowPosition(200, 100);

    glutWindowId = glutCreateWindow(windowName.c_str());
    anyWindow[glutWindowId] = this;

    // Initialisation handlers
    glutReshapeFunc(BIND_CALLBACK(&minGL::callReshape));
    glutDisplayFunc(BIND_CALLBACK(&minGL::callDisplay));
    glutKeyboardFunc(BIND_CALLBACK(&minGL::callKeyboard));
    glutKeyboardUpFunc(BIND_CALLBACK(&minGL::callKeyboardUp));
    glutSpecialFunc(BIND_CALLBACK(&minGL::callKeyboardSpecial));
    glutSpecialUpFunc(BIND_CALLBACK(&minGL::callKeyboardUpSpecial));

    // Efface ecran
    clearScreen();

    // Un tour de boucle pour lancer l'affichage
    glutMainLoopEvent();
}

/*!
 *  \brief      Indique si la touche est pressée (true) ou pas (false)
 *  
 *  \return     Retourne `true` si la touche est pressée et `false` si elle ne l'est pas
 *  \param[in]  key : la touche concernée : code et spécial
 */
bool minGL::isPressed(const keyType &key)
{
    return keyboardMap[key];
}

//http://mperriss.free.fr/opengl/Guide_2D/texte.htm
//https://www.opengl.org/resources/libraries/glut/spec3/node76.html

/*!
 * \brief fonction qui affiche du texte à l'écran
 * \param[in] x : position x
 * \param[in] y : position y
 * \param[in] str : texte à afficher
 */
void minGL::displayText(const unsigned &x, const unsigned &y, const string &str)
{
    glRasterPos2f(x, y);
    for (unsigned i(0); i < str.size(); ++i)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
    }
}

void minGL::stopGaphic()
{
    glutDestroyWindow(glutWindowId);
    glutMainLoopEvent();
}

void minGL::callReshape(int h, int w)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, GLfloat(windowWidth), 0.0, GLfloat(windowHeight));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, h, w);
}
/*!
 * \brief fonction légèrement modifiée pour enlever le bug du texte clignotant
 * 
 * 
 */
void minGL::callDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glRasterPos2i(0, 0);
    glDrawPixels(windowWidth, windowHeight, GL_RGB, GL_UNSIGNED_BYTE, &screenBuffer[0]);
}
void minGL::callKeyboard(unsigned char k, int x, int y)
{
    keyType key(k, false);
    keyboardMap[key] = true;
}
void minGL::callKeyboardUp(unsigned char k, int x, int y)
{
    keyType key(k, false);
    keyboardMap[key] = false;
}

void minGL::callKeyboardSpecial(int k, int x, int y)
{
    keyType key(k, true);
    keyboardMap[key] = true;
}
void minGL::callKeyboardUpSpecial(int k, int x, int y)
{
    keyType key(k, true);
    keyboardMap[key] = false;
}

unsigned minGL::getWindowWidth() const
{
    return windowWidth;
}

unsigned minGL::getWindowHeight() const
{
    return windowHeight;
}
