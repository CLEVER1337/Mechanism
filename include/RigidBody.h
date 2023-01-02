#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <QOpenGLFunctions_3_3_Core>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Model.h"
#include "ShaderProgram.h"
#include "Camera.h"

class RigidBody
{
public:
    RigidBody();

    RigidBody(QOpenGLFunctions_3_3_Core &gl,
              nsGraphicsEngine::Camera camera,
              int widgetWidth,
              int widgetHeight,
              char* modelPath,
              const char* vertexShaderFileName,
              const char* fragmentShaderFileName);

    void SetupMainData(QOpenGLFunctions_3_3_Core &gl,
                       nsGraphicsEngine::Camera camera,
                       int widgetWidth,
                       int widgetHeight,
                       char* modelPath,
                       const char* vertexShaderFileName,
                       const char* fragmentShaderFileName);

    void Draw(QOpenGLFunctions_3_3_Core &gl);

    void SetupMatrices(nsGraphicsEngine::Camera camera);

    void SendMatrices(QOpenGLFunctions_3_3_Core &gl);

    int GetId();

    glm::vec3 globalPosition;
    glm::vec3 rotation;

    std::string name;

    static int GetIdCount();

private:
    nsGraphicsEngine::Model model;

    nsGraphicsEngine::ShaderProgram shaderProgram;

    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    int id;

    static int count;
};

int RigidBody::count = 0;

#endif // RIGIDBODY_H
