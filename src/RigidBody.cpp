#include "RigidBody.h"


RigidBody::RigidBody()
{
    id = count;
    count++;

    modelMatrix = glm::mat4(1.0);
    viewMatrix = glm::mat4(1.0);
    projectionMatrix = glm::mat4(1.0);
}

RigidBody::RigidBody(QOpenGLFunctions_3_3_Core &gl,
                     nsGraphicsEngine::Camera camera,
                     int widgetWidth,
                     int widgetHeight,
                     char* modelPath,
                     const char* vertexShaderFileName,
                     const char* fragmentShaderFileName)
    : RigidBody()
{
    SetupMainData(gl, camera, widgetWidth, widgetHeight, modelPath, vertexShaderFileName, fragmentShaderFileName);
}

void RigidBody::SetupMainData(QOpenGLFunctions_3_3_Core &gl,
                              nsGraphicsEngine::Camera camera,
                              int widgetWidth,
                              int widgetHeight,
                              char* modelPath,
                              const char* vertexShaderFileName,
                              const char* fragmentShaderFileName)
{
    model.LoadModel(gl, modelPath);
    shaderProgram.CreateShaderProgram(gl, vertexShaderFileName, fragmentShaderFileName);
    globalPosition = glm::vec3(0.0);
    name = std::to_string(id);

    projectionMatrix = glm::perspective<double>(glm::radians(camera.GetFov()), widgetWidth / widgetHeight, 0.1, 100);
}

void RigidBody::Draw(QOpenGLFunctions_3_3_Core &gl)
{
    model.Draw(gl, shaderProgram);
}

int RigidBody::GetId()
{
    return id;
}

int RigidBody::GetIdCount()
{
    return count;
}

void RigidBody::SetupMatrices(nsGraphicsEngine::Camera camera)
{
    modelMatrix = glm::translate(modelMatrix, globalPosition);
    modelMatrix = glm::rotate<float>(modelMatrix, 0, rotation);

    viewMatrix = glm::lookAt(camera.GetPos(), camera.GetPos() + camera.GetFront(), camera.GetUp());
}

void RigidBody::SendMatrices(QOpenGLFunctions_3_3_Core &gl)
{
    shaderProgram.SetMat4(gl, "", modelMatrix);
    shaderProgram.SetMat4(gl, "", viewMatrix);
    shaderProgram.SetMat4(gl, "", projectionMatrix);
}
