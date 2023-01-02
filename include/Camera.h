#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace nsGraphicsEngine
{
/*!
 * \struct Direction
 * \brief The direction
*/
enum Direction
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

/*!
 * \class Camera
 * \brief This class is for controll camera
*/
class Camera
{
public:
    /*!
     * \fn Camera()
     * \brief Standard constructor
    */
    Camera();

    Camera(float fov, float speed);

    /*!
     * \fn void MoveBySide(Direction direction, float deltaTime)
     * \brief This function is change positions vectors of camera
    */
    void MoveBySide(Direction direction, float deltaTime);
    /*!
     * \fn void Turn(int xOffset, int yOffset)
     * \brief This function is change rotation vectors of camera
    */
    void Turn(int xOffset, int yOffset);

    glm::vec3 GetPos();

    glm::vec3 GetFront();

    glm::vec3 GetUp();

    float GetFov();

private:
    /*!
     * \var glm::vec3 pos
     * \brief Camera's position vector
    */
    glm::vec3 pos;
    /*!
     * \var glm::vec3 front
     * \brief Camera's front direction vector
    */
    glm::vec3 front;
    /*!
     * \var glm::vec3 up
     * \brief Camera's up direction vector
    */
    glm::vec3 up;

    /*!
     * \var float pitch
     * \brief Rotating around y axis
    */
    float pitch;
    /*!
     * \var float yaw
     * \brief Rotating around z axis
    */
    float yaw;

    /*!
     * \var float speed
     * \brief Camera's movement speed
    */
    float speed;

    /*!
     * \var float fov
     * \brief Camera's field of view in degrees
    */
    float fov;

    /*!
     * \fn void Update(float deltaTime)
     * \brief This function is update values which depend by deltaTime value
    */
    void Update(float deltaTime);
};
}

#endif // CAMERA_H
