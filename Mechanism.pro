QT += core gui
QT += opengl



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



#external libs#
LIBS += -lopengl32

#compiler settings#
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

#source files#
SOURCES += \
    src/MainOpenGLClass.cpp \
    src/Main.cpp \
    src/MainWindow.cpp \
    src/ShaderProgram.cpp \
    src/TextureLoader.cpp

#header files#
HEADERS += \
    include/MainOpenGLClass.h \
    include/MainWindow.h \
    include/ShaderProgram.h \
    include/TextureLoader.h

#form files#
FORMS += \
    ui/MainWindow.ui

#include folder#
INCLUDEPATH += \
    include/ \
    include/glm/

#QT default rules#
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/Shaders.qrc
