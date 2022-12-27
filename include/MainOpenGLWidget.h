#ifndef MAINOPENGLCLASS_H
#define MAINOPENGLCLASS_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ShaderProgram.h"
#include "Camera.h"
#include "Controller.h"

class MainOpenGLWidget : public QOpenGLWidget
{
public:
    MainOpenGLWidget(QWidget* parent = nullptr);
    ~MainOpenGLWidget();

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    QOpenGLFunctions_3_3_Core gl;

    nsGraphicsEngine::Camera camera;
    nsGraphicsEngine::Controller controller;

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    glm::vec2 screenSize;

    float deltaTime, lastFrameTime;
};

#endif // MAINOPENGLCLASS_H
