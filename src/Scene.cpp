#include "Scene.h"

Scene::Scene()
{
}

void Scene::Draw(QOpenGLFunctions_3_3_Core &gl)
{
    for(int i = 0; i < objects.size(); i++)
    {
        objects[i].SetupMatrices(camera);
        objects[i].SendMatrices(gl);
        objects[i].Draw(gl);
    }
}

void Scene::SetupObjectsData(QOpenGLFunctions_3_3_Core &gl,
                             nsGraphicsEngine::Camera camera,
                             int widgetWidth,
                             int widgetHeight,
                             char *modelPath,
                             const char *vertexShaderFileName,
                             const char *fragmentShaderFileName)
{
    for(int i = 0; i < objects.size(); i++)
    {
        objects[i].SetupMainData(gl, camera, widgetWidth, widgetHeight, modelPath, vertexShaderFileName, fragmentShaderFileName);
    }
}

nsGraphicsEngine::Camera& Scene::GetCamera()
{
    return camera;
}
