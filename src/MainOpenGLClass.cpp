#include <QOpenGLWidget>
#include <QtDebug>
#include <QTimer>
#include <QTime>
#include <QKeyEvent>

#include "MainOpenGLClass.h"

MainOpenGLClass::MainOpenGLClass(QWidget* parent) : QOpenGLWidget(parent)
{

}

MainOpenGLClass::~MainOpenGLClass()
{

}

void MainOpenGLClass::initializeGL()
{
    gl.initializeOpenGLFunctions();

    cameraPos = glm::vec3(0.0, 0.0, 3.0);
    cameraFront = glm::vec3(0.0, 0.0, -1.0);
    cameraUp = glm::vec3(0.0, 1.0, 0.0);

    InitTriangle();

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(0);

    for(int i = 0; i < 10240; i++)
        keys[i] = false;

    deltaTime = 0.0;
    lastFrameTime = 0.0;

    this->setCursor(Qt::BlankCursor);

    posX = 0;
    posY = 0;

    pitch = 0.0;
    yaw = -90.0;

    fov = 45.0;
}

void MainOpenGLClass::resizeGL(int w, int h)
{
    screenW = w;
    screenH = h;
    gl.glViewport(0, 0, screenW, screenH);
}

void MainOpenGLClass::paintGL()
{
    QTime time;

    float tmpDelta = time.currentTime().msec() - lastFrameTime;

    deltaTime = tmpDelta >= 0.0 ? tmpDelta : 0.0;
    lastFrameTime = time.currentTime().msec();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    CameraMove();



    shaderProgram.UseShaderProgram(gl);



    glm::vec3 lightPos(1.2, 1.0, 2.0);

    GLint lightPosLocation = gl.glGetUniformLocation(shaderProgram.GetShaderProgram(), "light_pos");
    gl.glUniform3f(lightPosLocation, lightPos.x, lightPos.y, lightPos.z);

    GLint objectColorLocation = gl.glGetUniformLocation(shaderProgram.GetShaderProgram(), "object_color");
    gl.glUniform3f(objectColorLocation, 1.0, 0.5, 0.31);

    GLint lightColorLocation = gl.glGetUniformLocation(shaderProgram.GetShaderProgram(), "light_color");
    gl.glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);

    GLint viewPosLocation = gl.glGetUniformLocation(shaderProgram.GetShaderProgram(), "view_pos");
    gl.glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);



    glm::mat4 view = glm::mat4(1.0);
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    glm::mat4 projection = glm::mat4(1.0);
    projection = glm::perspective<double>(glm::radians(fov), screenW / screenH, 0.1, 100.0);

    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
    model = glm::rotate<float>(model, 0, glm::vec3(0.5, 1.0, 0.0));

    GLint modelLocation = gl.glGetUniformLocation(shaderProgram.GetShaderProgram(), "model");
    gl.glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

    GLint viewLocation = gl.glGetUniformLocation(shaderProgram.GetShaderProgram(), "view");
    gl.glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

    GLint projectionLocation = gl.glGetUniformLocation(shaderProgram.GetShaderProgram(), "projection");
    gl.glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));



    gl.glBindVertexArray(VAO);

    gl.glDrawArrays(GL_TRIANGLES, 0, 36);

    gl.glBindVertexArray(0);



    lightShaderProgram.UseShaderProgram(gl);

    glm::mat4 lightModel = glm::mat4(1.0);
    lightModel = glm::translate(lightModel, lightPos);
    lightModel = glm::scale(lightModel, glm::vec3(0.7f));

    glm::mat4 lightView = glm::mat4(1.0);
    lightView = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    glm::mat4 lightProjection = glm::mat4(1.0);
    lightProjection = glm::perspective<double>(glm::radians(fov), screenW / screenH, 0.1, 100.0);



    GLint lightModelLocation = gl.glGetUniformLocation(lightShaderProgram.GetShaderProgram(), "model");
    gl.glUniformMatrix4fv(lightModelLocation, 1, GL_FALSE, glm::value_ptr(lightModel));

    GLint lightViewLocation = gl.glGetUniformLocation(lightShaderProgram.GetShaderProgram(), "view");
    gl.glUniformMatrix4fv(lightViewLocation, 1, GL_FALSE, glm::value_ptr(lightView));

    GLint lightProjectionLocation = gl.glGetUniformLocation(lightShaderProgram.GetShaderProgram(), "projection");
    gl.glUniformMatrix4fv(lightProjectionLocation, 1, GL_FALSE, glm::value_ptr(lightProjection));



    gl.glBindVertexArray(lightVAO);

    gl.glDrawArrays(GL_TRIANGLES, 0, 36);

    gl.glBindVertexArray(0);
}

void MainOpenGLClass::keyPressEvent(QKeyEvent* event)
{
    keys[event->nativeVirtualKey()] = true;
}

void MainOpenGLClass::keyReleaseEvent(QKeyEvent* event)
{
    keys[event->nativeVirtualKey()] = false;
}

void MainOpenGLClass::wheelEvent(QWheelEvent *event)
{
    if(fov >= 1.0 && fov <= 45.0)
        fov -= event->delta() / 25;
    if(fov <= 1.0)
        fov = 1.0;
    if(fov >= 45.0)
        fov = 45.0;
}

void MainOpenGLClass::MouseMove()
{
    float sensetivity = 0.1;

    _mouseLastX = this->cursor().pos().x();
    _mouseLastY = this->cursor().pos().y();

    if(this->cursor().pos().x() == 0)
    {
        posX -= 1024 / 2;
        this->cursor().setPos(1024 / 2, _mouseLastY);
    }
    else if(this->cursor().pos().x() == 1023)
    {
        posX += 1024 / 2;
        this->cursor().setPos(1024 / 2, _mouseLastY);
    }
    if(this->cursor().pos().y() == 0)
    {
        posY -= 768 / 2;
        this->cursor().setPos(_mouseLastX, 768 / 2);
    }
    else if(this->cursor().pos().y() == 767)
    {
        posY += 768 / 2;
        this->cursor().setPos(_mouseLastX, 768 / 2);
    }

    mouseX = posX + this->cursor().pos().x();
    mouseY = posY + this->cursor().pos().y();

    float xOffset = (mouseX - mouseLastX) * sensetivity;
    float yOffset = (mouseY - mouseLastY) * sensetivity;

    mouseLastX = mouseX;
    mouseLastY = mouseY;
    yaw += xOffset;
    pitch += yOffset;

    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(-glm::radians(pitch));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    cameraFront = glm::normalize(front);
}

void MainOpenGLClass::InitTriangle()
{
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };



    shaderProgram.CreateShaderProgram(gl, ":/SHADERS/VertShader.vert", ":/SHADERS/FragShader.frag");
    lightShaderProgram.CreateShaderProgram(gl, ":/SHADERS/LightVertShader.vert", ":/SHADERS/LightFragShader.frag");



    gl.glGenVertexArrays(1, &VAO);
    gl.glGenBuffers(1, &VBO);

    gl.glBindVertexArray(VAO);

    gl.glBindBuffer(GL_ARRAY_BUFFER, VBO);
    gl.glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    gl.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    gl.glEnableVertexAttribArray(0);

    gl.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    gl.glEnableVertexAttribArray(1);

    gl.glBindVertexArray(0);



    gl.glGenVertexArrays(1, &lightVAO);
    gl.glGenBuffers(1, &lightVBO);

    gl.glBindVertexArray(lightVAO);

    gl.glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    gl.glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    gl.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    gl.glEnableVertexAttribArray(0);

    gl.glBindVertexArray(0);
}

void MainOpenGLClass::CameraMove()
{
    float cameraSpeed = 0.01 * deltaTime;
    if(keys[(int)'W'])
      cameraPos += cameraSpeed * cameraFront;
    if(keys[(int)'S'])
      cameraPos -= cameraSpeed * cameraFront;
    if(keys[(int)'A'])
      cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if(keys[(int)'D'])
      cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    MouseMove();
}

