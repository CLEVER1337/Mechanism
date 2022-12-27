#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <QGLFunctions>
#include <QOpenGLFunctions_3_3_Core>
#include <QImage>

namespace nsGraphicsEngine
{
/*!
 * \class TextureLoader
 * \brief This class is loading texture
*/
class TextureLoader
{
public:
    /*!
     * \fn TextureLoader()
     * \brief Standard constructor
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
     * Return: texture id
    */
    GLuint GetTextureId();

private:
    /*!
     * \var GLuint texture
     * \brief Texture
    */
    GLuint texture;

    /*!
     * \fn void GenereteTexture(QOpenGLFunctions_3_3_Core &gl)
     * \brief This function generate texture
    */
    void GenerateTexture(QOpenGLFunctions_3_3_Core &gl);

    /*!
     * \fn void LoadTexture(QOpenGLFunctions_3_3_Core &gl, const char* textureFileName)
     * \brief This function load texture
    */
    void LoadTexture(QOpenGLFunctions_3_3_Core &gl, const char* textureFileName);
};
}

#endif // TEXTURELOADER_H
