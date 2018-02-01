TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp \
    transformation.cpp \
    camera.cpp \
#    model.cpp \
    texture.cpp \
    resourcemanager.cpp \
    mesh.cpp \
    material.cpp


LIBS += -lglut
LIBS +=  -lGL
LIBS += -lGLEW
LIBS += `pkg-config opencv --libs`
LIBS += -L/home/annusha/libs/assimp/lib -lassimp

INCLUDEPATH += -L/usr/lib/
INCLUDEPATH += -L/home/annusha/libs/assimp/include

#PRE_TARGETDEPS += /home/annusha/libs/assimp/lib/

HEADERS += \
    shader.h \
    render.h \
    transformation.h \
    camera.h \
    mesh.h \
#    model.h \
    texture.h \
    resourcemanager.h \
    material.h \
    parametrs.h \
    saturn_ring.h

DISTFILES += \
    vertex.vsh \
    fragment.fsh \
    sun.vsh \
    sun.fsh \
    fragment_ring.fsh
