QT += core gui
QT += opengl



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



#external libs#
LIBS += -lopengl32

LIBS += -L"$$PWD/lib" -lassimp.dll

#compiler settings#
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

#source files#
SOURCES += \
    src/Camera.cpp \
    src/Controller.cpp \
    src/Main.cpp \
    src/MainOpenGLWidget.cpp \
    src/MainWindow.cpp \
    src/Mesh.cpp \
    src/Model.cpp \
    src/RigidBody3D.cpp \
    src/ShaderProgram.cpp \
    src/TextureLoader.cpp

#header files#
HEADERS += \
    include/Camera.h \
    include/Controller.h \
    include/MainOpenGLWidget.h \
    include/MainWindow.h \
    include/Mesh.h \
    include/Model.h \
    include/RigidBody3D.h \
    include/ShaderProgram.h \
    include/TextureLoader.h

#form files#
FORMS += \
    ui/MainWindow.ui

#include folder#
INCLUDEPATH += \
    include/

#resources#
RESOURCES += \
    resource/Shaders.qrc

#QT default rules#
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
