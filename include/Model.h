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
/*!
 * \class Model
 * \brief This class loading and draw 3d model from file
*/
class Model
{
public:
    /*!
     * \fn Model()
     * \brief Standard constructor
    */
    Model();
    /*!
     * \fn Model(QOpenGLFunctions_3_3_Core &gl, char* path)
     * \brief This constructor loading model
    */
    Model(QOpenGLFunctions_3_3_Core &gl, char* path);

    /*!
     * \fn void Draw(QOpenGLFunctions_3_3_Core &gl, nsUtility::ShaderProgram shaderProgram)
     * \brief This function draw 3d model
    */
    void Draw(QOpenGLFunctions_3_3_Core &gl, nsUtility::ShaderProgram shaderProgram);

private:
    /*!
     * \var std::vector<Mesh> meshes
     * \brief 3d meshes
    */
    std::vector<Mesh> meshes;
    /*!
     * \var std::vector<TextureData> texturesLoaded
     * \brief Already loaded textures
    */
    std::vector<TextureData> texturesLoaded;
    /*!
     * \var std::string directory
     * \brief Directory of 3d model
    */
    std::string directory;

    /*!
     * \fn void LoadModel(QOpenGLFunctions_3_3_Core &gl, std::string path)
     * \brief This function load 3d model
    */
    void LoadModel(QOpenGLFunctions_3_3_Core &gl, std::string path);
    /*!
     * \fn void ProccesNode(QOpenGLFunctions_3_3_Core &gl, aiNode* node, const aiScene* scene)
     * \brief This function adaptate node
    */
    void AdaptateNode(QOpenGLFunctions_3_3_Core &gl, aiNode* node, const aiScene* scene);
    /*!
     * \fn void ProcessNode(QOpenGLFunctions_3_3_Core &gl, aiNode* node, const aiScene* scene)
     * \brief This function adaptate node's meshes
    */
    Mesh AdaptateMesh(QOpenGLFunctions_3_3_Core &gl, aiMesh* mesh, const aiScene* scene);
    /*!
     * \fn void std::vector<TextureData> LoadMaterialTexture(QOpenGLFunctions_3_3_Core &gl, aiMaterial* material, aiTextureType type, TextureType typeName)
     * \brief This function loading material
    */
    std::vector<TextureData> LoadMaterialTexture(QOpenGLFunctions_3_3_Core &gl, aiMaterial* material, aiTextureType type, TextureType typeName);
};
}

#endif // MODEL_H
