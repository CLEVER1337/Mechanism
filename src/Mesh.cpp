#include "Mesh.h"

namespace nsUtility
{
Mesh::Mesh()
{
}

Mesh::Mesh(QOpenGLFunctions_3_3_Core &gl, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureData> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    SetupMesh(gl);
}

void Mesh::Draw(QOpenGLFunctions_3_3_Core &gl, nsUtility::ShaderProgram shaderProgram)
{
    unsigned int diffuseN = 1, specularN = 1;

    for(unsigned int i = 0; i < textures.size(); i++)
    {
        gl.glActiveTexture(GL_TEXTURE0 + i);

        TextureType type = textures[i].type;

        switch(type)
        {
        case DIFFUSE:
            diffuseN++;
            break;
        case SPECULAR:
            specularN++;
            break;
        }

        char tmpBuf[100];

        std::string diffuseNStr = itoa(diffuseN,tmpBuf, 10);
        std::string specularNStr = itoa(specularN,tmpBuf, 10);

        std::string typeNNum = type == DIFFUSE ? ("diffuse" + diffuseNStr) : ("specular" + specularNStr);

        GLint textureLocation = gl.glGetUniformLocation(shaderProgram.GetShaderProgram(), ("material." + typeNNum).c_str());
        gl.glUniform1f(textureLocation, i);

        gl.glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    gl.glActiveTexture(GL_TEXTURE0);

    gl.glBindVertexArray(VAO);
    gl.glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    gl.glBindVertexArray(0);

    gl.glActiveTexture(GL_TEXTURE0);
}

void Mesh::SetupMesh(QOpenGLFunctions_3_3_Core &gl)
{
    gl.glGenVertexArrays(1, &VAO);
    gl.glGenBuffers(1, &VBO);
    gl.glGenBuffers(1, &EBO);

    gl.glBindVertexArray(VAO);
    gl.glBindBuffer(GL_ARRAY_BUFFER, VBO);

    gl.glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    gl.glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    gl.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    gl.glEnableVertexAttribArray(0);

    gl.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    gl.glEnableVertexAttribArray(1);

    gl.glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    gl.glEnableVertexAttribArray(2);
}
}
