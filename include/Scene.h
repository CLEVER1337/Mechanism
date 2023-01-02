#ifndef SCENE_H
#define SCENE_H

#include "RigidBody.h"
#include "Camera.h"

class Scene
{
public:
    Scene();

    void Draw(QOpenGLFunctions_3_3_Core &gl);

    void SetupObjectsData(QOpenGLFunctions_3_3_Core &gl,
                          nsGraphicsEngine::Camera camera,
                          int widgetWidth,
                          int widgetHeight,
                          char* modelPath,
                          const char* vertexShaderFileName,
                          const char* fragmentShaderFileName);

    nsGraphicsEngine::Camera& GetCamera();

private:
    std::vector<RigidBody> objects;

    nsGraphicsEngine::Camera camera;
};

#endif // SCENE_H
