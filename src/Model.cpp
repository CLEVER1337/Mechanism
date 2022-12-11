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

void Model::Draw(QOpenGLFunctions_3_3_Core &gl, nsUtility::ShaderProgram shaderProgram)
{
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(gl, shaderProgram);
}

void Model::LoadModel(QOpenGLFunctions_3_3_Core &gl, std::string path)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    directory = path.substr(0, path.find_last_of('/'));

    ProccesNode(gl, scene->mRootNode, scene);
}

void Model::ProccesNode(QOpenGLFunctions_3_3_Core &gl, aiNode* node, const aiScene* scene)
{
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProccesMesh(gl, mesh, scene));
    }

    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProccesNode(gl, node->mChildren[i], scene);
    }
}

Mesh Model::ProccesMesh(QOpenGLFunctions_3_3_Core &gl, aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<TextureData> textures;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;

        glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;

        vertex.position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;

        vertex.normal = vector;

        if(mesh->mTextureCoords[0])
        {
            glm::vec2 vector2;

            vector2.x = mesh->mTextureCoords[0][i].x;
            vector2.y = mesh->mTextureCoords[0][i].y;

            vertex.texCoords = vector2;
        }
        else
        {
            vertex.texCoords = glm::vec2(0.0, 0.0);
        }

        vertices.push_back(vertex);
    }

    //indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for(unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    //materials
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<TextureData> diffuseMaps = LoadMaterialTexture(gl, material, aiTextureType_DIFFUSE, DIFFUSE);

        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<TextureData> specularMaps = LoadMaterialTexture(gl, material, aiTextureType_SPECULAR, SPECULAR);

        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(gl, vertices, indices, textures);
}

std::vector<TextureData> Model::LoadMaterialTexture(QOpenGLFunctions_3_3_Core &gl, aiMaterial* material, aiTextureType type, TextureType typeName)
{
    std::vector<TextureData> textures;

    for(unsigned int i = 0; i < material->GetTextureCount(type); i++)
    {
        aiString str;
        material->GetTexture(type, i, &str);
        bool skip = false;

        for(unsigned int j = 0; j < texturesLoaded.size(); j++)
        {
            if(std::strcmp(texturesLoaded[j].path.C_Str(), str.C_Str()))
            {
                textures.push_back(texturesLoaded[j]);
                skip = true;
                break;
            }
        }

        if(!skip)
        {
            TextureData texture;

            nsUtility::TextureLoader textureLoader(gl, str.C_Str());

            texture.id = textureLoader.GetTextureId();
            texture.type = typeName;
            texture.path = str;
            textures.push_back(texture);
            texturesLoaded.push_back(texture);
        }
    }

    return textures;
}
}
