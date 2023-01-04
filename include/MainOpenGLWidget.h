#ifndef MAINOPENGLWIDGET_H
#define MAINOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QTimer>
#include <QTime>
#include <QKeyEvent>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Controller.h"
#include "Scene.h"

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

    nsGraphicsEngine::Controller controller;

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    glm::vec2 widgetSize;

    float deltaTime, lastFrameTime;

    Scene currentScene;
    std::vector<Scene> scenes;
};

#endif // MAINOPENGLWIDGET_H
