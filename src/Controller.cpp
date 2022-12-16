#include "Controller.h"

namespace nsUtility
{
Controller::Controller()
{
    for(int i = 0; i < 10240; i++)
        keys[i] = false;
}

void Controller::MouseMoveControll(Camera camera, QCursor cursor, int screenHeight, int screenWidth)
{
    if(cursor.pos().x() == 0)
    {
        mousePos.x -= screenWidth / 2;
        cursor.setPos(screenHeight / 2, cursor.pos().y());
    }
    else if(cursor.pos().x() == screenWidth - 1)
    {
        mousePos.x += screenWidth / 2;
        cursor.setPos(screenHeight / 2, cursor.pos().y());
    }
    if(cursor.pos().y() == 0)
    {
        mousePos.y -= screenHeight / 2;
        cursor.setPos(cursor.pos().x(), screenWidth / 2);
    }
    else if(cursor.pos().y() == screenHeight - 1)
    {
        mousePos.y += screenHeight / 2;
        cursor.setPos(cursor.pos().x(), screenWidth / 2);
    }

    int xOffset = (mousePos.x - mouseLastPos.x) * sensetivity;
    int yOffset = (mousePos.y - mouseLastPos.y) * sensetivity;

    camera.Turn(xOffset, yOffset);

    mouseLastPos.x = cursor.pos().x();
    mouseLastPos.y = cursor.pos().y();
}

void Controller::KeyboardPressControll(Camera camera, float deltaTime)
{
    if(keys[(int)'W'])
        camera.MoveBySide(FORWARD, deltaTime);
    if(keys[(int)'S'])
        camera.MoveBySide(BACKWARD, deltaTime);
    if(keys[(int)'A'])
        camera.MoveBySide(LEFT, deltaTime);
    if(keys[(int)'D'])
        camera.MoveBySide(RIGHT, deltaTime);
}

void Controller::KeyPress(int virtualKey)
{
    keys[virtualKey] = true;
}

void Controller::KeyRelease(int virtualKey)
{
    keys[virtualKey] = false;
}
}
