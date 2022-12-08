#include "Model.h"

namespace nsUtility
{
Model::Model()
{
}

Model::Model(QOpenGLFunctions_3_3_Core &gl, char* path)
{
    LoadModel(gl, path);
}
}
