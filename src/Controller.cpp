#include "Controller.h"

namespace nsGraphicsEngine
{
Controller::Controller()
{
    /*All keys is off*/
    for(int i = 0; i < 10240; i++)
        keys[i] = false;
}

void Controller::MouseMoveControll(Camera camera, QCursor cursor, int widgetWidth, int widgetHeight)
/*React to mouse move*/
{
    /*For infinity controll(if cursor move to screen last pixel it will be moved to center)*/
    if(cursor.pos().x() == 0)
    {
        mousePos.x -= widgetWidth / 2;
        cursor.setPos(widgetHeight / 2, cursor.pos().y());
    }
    else if(cursor.pos().x() == widgetWidth - 1)
    {
        mousePos.x += widgetWidth / 2;
        cursor.setPos(widgetHeight / 2, cursor.pos().y());
    }
    if(cursor.pos().y() == 0)
    {
        mousePos.y -= widgetHeight / 2;
        cursor.setPos(cursor.pos().x(), widgetWidth / 2);
    }
    else if(cursor.pos().y() == widgetHeight - 1)
    {
        mousePos.y += widgetHeight / 2;
        cursor.setPos(cursor.pos().x(), widgetWidth / 2);
    }

    /*Offset between current and previous mouse's positions*/
    int xOffset = (mousePos.x - mouseLastPos.x) * sensetivity;
    int yOffset = (mousePos.y - mouseLastPos.y) * sensetivity;

    camera.Turn(xOffset, yOffset);

    mouseLastPos.x = cursor.pos().x();
    mouseLastPos.y = cursor.pos().y();
}

void Controller::KeyboardPressControll(Camera camera, float deltaTime)
/*React when key si pressed*/
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
/*Press key*/
{
    keys[virtualKey] = true;
}

void Controller::KeyRelease(int virtualKey)
/*Release key*/
{
    keys[virtualKey] = false;
}
}
