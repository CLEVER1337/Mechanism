#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QCursor>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Camera.h"

namespace nsUtility
{
class Controller
{
public:
    Controller();

    void MouseMoveControll(Camera camera, QCursor cursor, int screenHeight, int screenWidth);
    void KeyboardPressControll(Camera camera, float deltaTime);
    void KeyPress(int virtualKey);
    void KeyRelease(int virtualKey);

private:
    float sensetivity = 0.1;

    glm::vec2 mousePos;
    glm::vec2 mouseLastPos;

    bool keys[10240];
};
}

#endif // CONTROLLER_H
