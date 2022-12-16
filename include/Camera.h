#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace nsUtility
{

enum SideWay
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    Camera();

    void MoveBySide(SideWay side, float deltaTime);
    void Turn(int xOffset, int yOffset);

private:
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;

    float pitch = 0.0;
    float yaw = -90.0;

    float speed = 0.01;

    float fov = 45.0;

    void Update(float deltaTime);
};
}

#endif // CAMERA_H
