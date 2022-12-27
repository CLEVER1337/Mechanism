#include "RigidBody3D.h"

namespace nsGraphicsEngine
{
RigidBody3D::RigidBody3D()
{
}

RigidBody3D::RigidBody3D(QOpenGLFunctions_3_3_Core &gl, glm::vec3 position, char* modelPath, const char* vertexShaderFileName, const char* fragmentShaderFileName)
    : model(gl, modelPath)
    , shaderProgram(gl, vertexShaderFileName, fragmentShaderFileName)
{
    globalPosition = position;
}

void RigidBody3D::Draw(QOpenGLFunctions_3_3_Core &gl)
{

}

void RigidBody3D::SetupMatrices()
{

}

void RigidBody3D::SendMatrices()
{

}
}
