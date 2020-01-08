TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    minGL/figs/basefig.cpp \
    minGL/figs/circle.cpp \
    minGL/figs/figure.cpp \
    minGL/figs/line.cpp \
    minGL/figs/rectangle.cpp \
    minGL/figs/triangle.cpp \
    minGL/graph/mingl.cpp \
    minGL/graph/rgbcolor.cpp \
    minGL/tools/CException.cxx \
    minGL/tools/myexception.cpp \
    minGL/tools/pixel.cpp \
    minGL/graph/iminglinjectable.cpp \
    minGL/tools/tools.cpp \
    minGL/tools/pixelexception.cpp \
    utils/loadconfig.cpp \
    utils/spaceinvaders.cpp

QT += opengl core gui

LIBS +=  -lglut -lGLU -lGL

#INCLUDEPATH += /opt/local/include/GL/
INCLUDEPATH += /usr/include/GL/

QMAKE_CXXFLAGS += -Wall

HEADERS += \
    minGL/figs/basefig.h \
    minGL/figs/circle.h \
    minGL/figs/figure.h \
    minGL/figs/line.h \
    minGL/figs/pos.h \
    minGL/figs/rectangle.h \
    minGL/figs/triangle.h \
    minGL/graph/libgraphique_fonts.h \
    minGL/graph/mingl.h \
    minGL/graph/pos.h \
    minGL/graph/rgbcolor.h \
    minGL/tools/CException.h \
    minGL/tools/CException.hxx \
    minGL/tools/CstCodErr.h \
    minGL/tools/IEditable.h \
    minGL/tools/IEditable.hxx \
    utils/entity.h \
    minGL/tools/myexception.h \
    minGL/tools/pixel.h \
    utils/loadconfig.h \
    utils/spaceinvaders.h \
    minGL/tools/tools.h \
    minGL/graph/iminglinjectable.h \
    minGL/tools/pixelexception.h
