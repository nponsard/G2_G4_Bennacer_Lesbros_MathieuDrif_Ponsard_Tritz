TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    nosFichiers/src/mainSpaceInvaders.cpp \
    nosFichiers/src/minGL/figs/basefig.cpp \
    nosFichiers/src/minGL/figs/circle.cpp \
    nosFichiers/src/minGL/figs/figure.cpp \
    nosFichiers/src/minGL/figs/line.cpp \
    nosFichiers/src/minGL/figs/rectangle.cpp \
    nosFichiers/src/minGL/figs/triangle.cpp \
    nosFichiers/src/minGL/graph/mingl.cpp \
    nosFichiers/src/minGL/graph/rgbcolor.cpp \
    nosFichiers/src/minGL/tools/CException.cxx \
    nosFichiers/src/minGL/tools/myexception.cpp \
    nosFichiers/src/minGL/tools/pixel.cpp \
    nosFichiers/src/minGL/graph/iminglinjectable.cpp \
    nosFichiers/src/minGL/tools/tools.cpp \
    nosFichiers/src/minGL/tools/pixelexception.cpp \
    nosFichiers/src/utils/display.cpp \
    nosFichiers/src/utils/keyboardInput.cpp \
    nosFichiers/src/utils/loadconfig.cpp \
    nosFichiers/src/utils/loadscore.cpp \
    nosFichiers/src/utils/savescores.cpp \
    nosFichiers/src/utils/scoresort.cpp \
    nosFichiers/src/utils/spaceinvaders.cpp \
    nosFichiers/src/utils/music.cpp

QT += opengl core gui

LIBS +=  -lglut -lGLU -lGL

#INCLUDEPATH += /opt/local/include/GL/
INCLUDEPATH += /usr/include/GL/

QMAKE_CXXFLAGS += -Wall

HEADERS += \
    nosFichiers/src/mainSpaceInvaders.h \
    nosFichiers/src/minGL/figs/basefig.h \
    nosFichiers/src/minGL/figs/circle.h \
    nosFichiers/src/minGL/figs/figure.h \
    nosFichiers/src/minGL/figs/line.h \
    nosFichiers/src/minGL/figs/pos.h \
    nosFichiers/src/minGL/figs/rectangle.h \
    nosFichiers/src/minGL/figs/triangle.h \
    nosFichiers/src/minGL/graph/libgraphique_fonts.h \
    nosFichiers/src/minGL/graph/mingl.h \
    nosFichiers/src/minGL/graph/pos.h \
    nosFichiers/src/minGL/graph/rgbcolor.h \
    nosFichiers/src/minGL/tools/CException.h \
    nosFichiers/src/minGL/tools/CException.hxx \
    nosFichiers/src/minGL/tools/CstCodErr.h \
    nosFichiers/src/minGL/tools/IEditable.h \
    nosFichiers/src/minGL/tools/IEditable.hxx \
    nosFichiers/src/utils/display.h \
    nosFichiers/src/utils/entity.h \
    nosFichiers/src/minGL/tools/myexception.h \
    nosFichiers/src/minGL/tools/pixel.h \
    nosFichiers/src/utils/keyboardInput.h \
    nosFichiers/src/utils/loadScores.h \
    nosFichiers/src/utils/loadconfig.h \
    nosFichiers/src/utils/savescores.h \
    nosFichiers/src/utils/scoresort.h \
    nosFichiers/src/utils/spaceinvaders.h \
    nosFichiers/src/minGL/tools/tools.h \
    nosFichiers/src/minGL/graph/iminglinjectable.h \
    nosFichiers/src/minGL/tools/pixelexception.h \
    nosFichiers/src/utils/music.h
