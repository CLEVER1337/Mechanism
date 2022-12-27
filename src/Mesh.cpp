#include "Mesh.h"

namespace nsGraphicsEngine
{
Mesh::Mesh()
{
}

Mesh::Mesh(QOpenGLFunctions_3_3_Core &gl, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureData> textures)
/*Set data and setup mesh*/
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    SetupMesh(gl);
}

void Mesh::Draw(QOpenGLFunctions_3_3_Core &gl, nsGraphicsEngine::ShaderProgram shaderProgram)
/*Render mesh*/
{
    unsigned int diffuseNum = 1, specularNum = 1;

    for(unsigned int i = 0; i < textures.size(); i++)
    {
        gl.glActiveTexture(GL_TEXTURE0 + i);

        TextureType type = textures[i].type;

        if(type == DIFFUSE)
            diffuseNum++;
        else if(type == SPECULAR)
            specularNum++;

        /*Change "material." to shader's uniform name*/
        std::string uniformTextureVarName = "material." + (type == DIFFUSE ? ("diffuse" + std::to_string(diffuseNum))
                                                                           : ("specular" + std::to_string(specularNum)));

        shaderProgram.SetInt(gl, uniformTextureVarName.c_str(), textures[i].id);

        gl.glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    gl.glActiveTexture(GL_TEXTURE0);

    gl.glBindVertexArray(VAO);
    gl.glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    /*Good practice*/
    gl.glBindVertexArray(0);
    gl.glActiveTexture(GL_TEXTURE0);
}

void Mesh::SetupMesh(QOpenGLFunctions_3_3_Core &gl)
/*Setup video memory controllers fro this polygon mesh*/
{
    /*Generate objects*/
    gl.glGenVertexArrays(1, &VAO);
    gl.glGenBuffers(1, &VBO);
    gl.glGenBuffers(1, &EBO);

    /*Bind and create objects*/
    gl.glBindVertexArray(VAO);

    gl.glBindBuffer(GL_ARRAY_BUFFER, VBO);
    gl.glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    gl.glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    /*Set rules for reading and writing from generic vertex attribute data*/
    gl.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    gl.glEnableVertexAttribArray(0);

    gl.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    gl.glEnableVertexAttribArray(1);

    gl.glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    gl.glEnableVertexAttribArray(2);

    /*Good practice*/
    gl.glBindVertexArray(0);
}
}
