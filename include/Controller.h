#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QCursor>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Camera.h"

namespace nsGraphicsEngine
{
/*!
 * \class Controller
 * \brief This class is for controlling mouse and keyboard in MainOpenGLWidget
*/
class Controller
{
public:
    /*!
     * \fn Controller()
     * \brief Standard constructor
    */
    Controller();

    /*!
     * \fn void MouseMoveControll(Camera camera, QCursor cursor, int screenHeight, int screenWidth)
     * \brief This function is react to mouse move
    */
    void MouseMoveControll(Camera camera, QCursor cursor, int screenHeight, int screenWidth);
    /*!
     * \fn void KeyboardPressControll(Camera camera, float deltaTime)
     * \brief This function is react to keyboard keys press
    */
    void KeyboardPressControll(Camera camera, float deltaTime);
    /*!
     * \fn void KeyPress(int virtualKey)
     * \brief This function is set key's flag to true when whis key is pressed
    */
    void KeyPress(int virtualKey);
    /*!
     * \fn void KeyRelease(int virtualKey)
     * \brief This function is set key's flag to false when whis key is released
    */
    void KeyRelease(int virtualKey);

private:
    /*!
     * \var float sensetivity
     * \brief Mouse's sensetivity
    */
    float sensetivity = 0.1;

    /*!
     * \var glm::vec2 mousePos
     * \brief Mouse's position in global space(it means max value is more than sreen's size)
    */
    glm::vec2 mousePos;
    /*!
     * \var glm::vec2 mouseLastPos
     * \brief Mouse's previous position in global space
    */
    glm::vec2 mouseLastPos;

    /*!
     * \var bool keys[10240]
     * \brief Flags for all keys on keyboard
    */
    bool keys[10240];
};
}

#endif // CONTROLLER_H
