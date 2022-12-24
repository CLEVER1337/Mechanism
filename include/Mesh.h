#ifndef MESH_H
#define MESH_H

#include <QOpenGLFunctions_3_3_Core>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "ShaderProgram.h"
#include "TextureLoader.h"

namespace nsUtility
{
/*!
 * \struct Vertex
 * \brief The vertex struct
*/
struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

/*!
 * \enum TextureType
 * \brief The texture type enum
*/
enum TextureType
{
    DIFFUSE,
    SPECULAR
};

/*!
 * \struct TextureData
 * \brief The texture data struct
*/
struct TextureData
{
    GLuint id;
    TextureType type;
    aiString path;
};

/*!
 * \class Mesh
 * \brief This class is loading polygon meshes
*/
class Mesh
{
public:
    /*!
     * \fn Mesh()
     * \brief Standard constructor
    */
    Mesh();
    /*!
     * \fn Mesh(QOpenGLFunctions_3_3_Core &gl, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureData> textures)
     * \brief This constructor is set all data and setup the mesh
    */
    Mesh(QOpenGLFunctions_3_3_Core &gl, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureData> textures);

    /*!
     * \fn void Draw(QOpenGLFunctions_3_3_Core &gl, nsUtility::ShaderProgram shaderProgram)
     * \brief This function draw polygon mesh
    */
    void Draw(QOpenGLFunctions_3_3_Core &gl, nsUtility::ShaderProgram shaderProgram);

private:
    /*!
     * \var GLuint VBO
     * \brief Vertex Buffer Object
    */
    GLuint VBO;
    /*!
     * \var GLuint VAO
     * \brief Vertex Array Object
    */
    GLuint VAO;
    /*!
     * \var GLuint EBO
     * \brief Element Buffer Object
    */
    GLuint EBO;

    /*!
     * \var std::vector<Vertex> vertices
     * \brief Vertices
    */
    std::vector<Vertex> vertices;
    /*!
     * \var std::vector<unsigned int> indices
     * \brief Indices
    */
    std::vector<unsigned int> indices;
    /*!
     * \var std::vector<TextureData> textures
     * \brief Textures
    */
    std::vector<TextureData> textures;

    /*!
     * \fn void SetupMesh(QOpenGLFunctions_3_3_Core &gl)
     * \brief This function setup polygon mesh
    */
    void SetupMesh(QOpenGLFunctions_3_3_Core &gl);
};
}

#endif // MESH_H
