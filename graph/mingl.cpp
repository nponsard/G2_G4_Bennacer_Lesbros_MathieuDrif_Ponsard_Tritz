#include <map>

#include "mingl.h"

using namespace std;
using namespace nsUtil;

//astuce pour faire passer les handlers en fonction static dans initGraphic ()
namespace {
map<int, minGL *> anyWindow;

template<typename T, T oHandler>
struct callBackBuilder;

template<typename Obj, typename... Arg, void(Obj::* oHandler)(Arg...)>
struct callBackBuilder<void(Obj::*)(Arg...), oHandler>
{
    static void callback(Arg... arg)
    {
        int current_id = glutGetWindow();
        //cout << "window [" << current_id << "] handler call" << endl;
        auto it = anyWindow.find(current_id);
        if(it != anyWindow.end())
        {
            (it->second->*oHandler)(arg...);
        }
    }
};
}

#define BIND_CALLBACK(HANDLER) callBackBuilder<decltype(HANDLER), HANDLER>::callback

minGL::minGL(const unsigned &Width, const unsigned &Height, const std::string &Name) :
    windowWidth (Width),
    windowHeight (Height),
    windowName (Name)
{
    screenBuffer.resize(Width * Height * 3);
   // initGlut();
   // initGraphic();
}

minGL::~minGL()
{
    auto it = anyWindow.find(glutWindowId);
    if(it != anyWindow.end())
        anyWindow.erase(it);
    stopGaphic();
}

void minGL::updateGraphic()
{
    glutPostRedisplay();
    glutMainLoopEvent();
}

void minGL::clearScreen() throw (myexception)
{
    for (unsigned i (0); i < windowWidth; ++i)
            for (unsigned j (0); j < windowHeight; ++j)
                setPixel(pos (i, j), bgColor);
}

void minGL::setPixel(const pos &pos_, const RGBcolor &col) throw (PixelException)
{

    //if (pos_.abs > windowWidth) throw myexception (kErrTooRight);
    //if (pos_.ord > windowHeight) throw myexception (kErrTooHight);
    if (pos_.abs > windowWidth) throw PixelException (pos_, col, "Pixel too right");
    if (pos_.ord > windowHeight) throw PixelException (pos_, col, "Pixel too high");

    screenBuffer[3*(pos_.ord*windowWidth+pos_.abs)+0] = col.Red;
    screenBuffer[3*(pos_.ord*windowWidth+pos_.abs)+1] = col.Green;
    screenBuffer[3*(pos_.ord*windowWidth+pos_.abs)+2] = col.Blue;
}


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
        return(key);

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
    glutSpecialFunc(BIND_CALLBACK(&minGL::callKeyboardSpecial));

    // Efface ecran
    clearScreen();

    // Un tour de boucle pour lancer l'affichage
    glutMainLoopEvent();
}

void minGL::stopGaphic()
{
    glutDestroyWindow(glutWindowId);
    glutMainLoopEvent();
}

void minGL::callReshape(int h, int w) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, GLfloat (windowWidth), 0.0, GLfloat (windowHeight));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,h,w);
}

void minGL::callDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glRasterPos2i(0,0);
    glDrawPixels(windowWidth, windowHeight, GL_RGB, GL_UNSIGNED_BYTE, &screenBuffer[0]);
    glFlush();
}


void minGL::callKeyboard(unsigned char key, int x, int y)
{
    keyboardBuffer.push(key);
   // cout << int (key) << endl;
}

void minGL::callKeyboardSpecial(int key, int x, int y)
{
    keyboardBuffer.push(key<<8);
}

unsigned minGL::getWindowWidth() const
{
    return windowWidth;
}

unsigned minGL::getWindowHeight() const
{
    return windowHeight;
}
