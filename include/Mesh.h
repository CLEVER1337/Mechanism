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
struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

enum TextureType
{
    DIFFUSE,
    SPECULAR
};

struct TextureData
{
    unsigned int id;
    TextureType type;
    aiString path;
};

class Mesh
{
public:
    Mesh();

    Mesh(QOpenGLFunctions_3_3_Core &gl, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureData> textures);

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<TextureData> textures;

    void Draw(QOpenGLFunctions_3_3_Core &gl, nsUtility::ShaderProgram shaderProgram);

private:
    GLuint VBO, VAO, EBO;

    void SetupMesh(QOpenGLFunctions_3_3_Core &gl);
};
}

#endif // MESH_H
