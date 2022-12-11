#ifndef MODEL_H
#define MODEL_H

#include <QOpenGLFunctions_3_3_Core>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "ShaderProgram.h"
#include "TextureLoader.h"
#include "Mesh.h"

namespace nsUtility
{
class Model
{
public:
    Model();

    Model(QOpenGLFunctions_3_3_Core &gl, char* path);

    void Draw(QOpenGLFunctions_3_3_Core &gl, nsUtility::ShaderProgram shaderProgram);

private:
    std::vector<Mesh> meshes;
    std::vector<TextureData> texturesLoaded;
    std::string directory;

    void LoadModel(QOpenGLFunctions_3_3_Core &gl, std::string path);
    void ProccesNode(QOpenGLFunctions_3_3_Core &gl, aiNode* node, const aiScene* scene);
    Mesh ProccesMesh(QOpenGLFunctions_3_3_Core &gl, aiMesh* mesh, const aiScene* scene);
    std::vector<TextureData> LoadMaterialTexture(QOpenGLFunctions_3_3_Core &gl, aiMaterial* material, aiTextureType type, TextureType typeName);
};
}

#endif // MODEL_H
