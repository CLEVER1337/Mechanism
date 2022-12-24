#ifndef MAINOPENGLCLASS_H
#define MAINOPENGLCLASS_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ShaderProgram.h"

class MainOpenGLWidget : public QOpenGLWidget
{
public:
    MainOpenGLWidget(QWidget* parent = nullptr);
    ~MainOpenGLWidget();

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent *event);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void wheelEvent(QWheelEvent *event);

    void MouseMove();

    void InitTriangle();

    void CameraMove();

private:
    QOpenGLFunctions_3_3_Core gl;

    GLuint VBO, VAO, EBO;
    GLuint lightVAO, lightVBO;
    nsUtility::ShaderProgram shaderProgram, lightShaderProgram;

    int screenW, screenH;

    float deltaTime, lastFrameTime;

    glm::vec3 cameraPos, cameraFront, cameraUp;

    bool keys[10240];

    float pitch, yaw;
    float mouseLastX = 1024 / 2;
    float mouseLastY = 768 / 2;
    float _mouseLastX, _mouseLastY;
    float mouseX, mouseY;
    int posX, posY;

    double fov;
};

#endif // MAINOPENGLCLASS_H
