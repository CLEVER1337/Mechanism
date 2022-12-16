#include "Camera.h"

namespace nsUtility
{
Camera::Camera()
{
}

void Camera::MoveBySide(SideWay side, float deltaTime)
{
    Update(deltaTime);

    switch (side)
    {
    case FORWARD:
        pos += speed * front;
        break;
    case BACKWARD:
        pos -= speed * front;
        break;
    case LEFT:
        pos -= glm::normalize(glm::cross(front, up)) * speed;
        break;
    case RIGHT:
        pos += glm::normalize(glm::cross(front, up)) * speed;
        break;
    }
}

void Camera::Turn(int xOffset, int yOffset)
{
    yaw += xOffset;
    pitch += yOffset;

    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 tmpFront;
    tmpFront.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    tmpFront.y = sin(-glm::radians(pitch));
    tmpFront.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    front = glm::normalize(tmpFront);
}

void Camera::Update(float deltaTime)
{
    speed *= deltaTime;
}
}
