#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <QGLFunctions>
#include <QOpenGLFunctions_3_3_Core>
#include <QImage>

namespace nsUtility
{
class TextureLoader
{
public:
    /*!
     * \fn TextureLoader()
     * \brief This constructor createing texture
    */
    TextureLoader();
    /*!
     * \fn TextureLoader(QOpenGLFunctions_3_3_Core &gl, const char* textureFileName)
     * \brief This constructor createing texture
    */
    TextureLoader(QOpenGLFunctions_3_3_Core &gl, const char* textureFileName);
    /*!
     * \fn void ActivateTexture(QOpenGLFunctions_3_3_Core &gl, GLuint shaderProgram, const char* textureUniformName, GLenum texture, int id)
     * \brief This function activate texture
    */
    void ActivateTexture(QOpenGLFunctions_3_3_Core &gl, GLuint shaderProgram, const char* textureUniformName, GLenum texture, int id);
    /*!
     * \fn void CreateTexture(QOpenGLFunctions_3_3_Core &gl, const char* textureFileNmae)
     * \brief This function createing texture
    */
    void CreateTexture(QOpenGLFunctions_3_3_Core &gl, const char* textureFileNmae);
    /*!
     * \fn GLuint GetTextureId()
     * \brief Getter for texture id
    */
    GLuint GetTextureId();

private:
    GLuint texture;

    void GenereteTexture(QOpenGLFunctions_3_3_Core &gl);

    void LoadTexture(QOpenGLFunctions_3_3_Core &gl, const char* textureFileName);
};
}

#endif // TEXTURELOADER_H
