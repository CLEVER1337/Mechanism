#include "Camera.h"

namespace nsGraphicsEngine
{
Camera::Camera()
{
    fov = 45.0;
    speed = 0.01;
    pitch = 0.0;
    yaw = -90.0;
    pos = glm::vec3(0.0);
    front = glm::vec3(0.0);
    up = glm::vec3(0.0);
}

Camera::Camera(float fov, float speed)
    : Camera()
{
    this->fov = fov;
    this->speed = speed;
}

void Camera::MoveBySide(Direction direction, float deltaTime)
/*Moving camera*/
{
    Update(deltaTime);

    switch (direction)
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
/*Rotating camera*/
{
    yaw += xOffset;
    pitch += yOffset;

    /*Block  y rotating to straight up and straight down*/
    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    /*Calculate camera's front vector*/
    glm::vec3 tmpFront;
    tmpFront.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    tmpFront.y = sin(-glm::radians(pitch));
    tmpFront.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    front = glm::normalize(tmpFront);
}

glm::vec3 Camera::GetPos(){
    return pos;
}

glm::vec3 Camera::GetFront(){
    return front;
}

glm::vec3 Camera::GetUp(){
    return up;
}

float Camera::GetFov(){
    return fov;
}

void Camera::Update(float deltaTime)
/*Updating*/
{
    speed *= deltaTime;
}
}
