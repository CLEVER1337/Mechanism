#ifndef RIGIDBODY3D_H
#define RIGIDBODY3D_H

#include <QOpenGLFunctions_3_3_Core>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Model.h"
#include "ShaderProgram.h"

namespace nsGraphicsEngine
{
class RigidBody3D
{
public:
    RigidBody3D();

    RigidBody3D(QOpenGLFunctions_3_3_Core &gl, glm::vec3 position, char* modelPath, const char* vertexShaderFileName, const char* fragmentShaderFileName);

    void Draw(QOpenGLFunctions_3_3_Core &gl);

private:
    nsGraphicsEngine::Model model;

    nsGraphicsEngine::ShaderProgram shaderProgram;

    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    glm::vec3 globalPosition;

    std::string name;

    int id;

    void SetupMatrices();

    void SendMatrices();
};
}

#endif // RIGIDBODY3D_H
