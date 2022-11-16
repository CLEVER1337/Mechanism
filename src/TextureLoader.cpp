#include "TextureLoader.h"

namespace nsUtility
{
TextureLoader::TextureLoader()
{
}

TextureLoader::TextureLoader(QOpenGLFunctions_3_3_Core &gl, const char* textureFileNmae)
/*Create texture*/
{
    CreateTexture(gl, textureFileNmae);
}

void TextureLoader::ActivateTexture(QOpenGLFunctions_3_3_Core &gl, GLuint shaderProgram, const char* textureUniformName, GLenum texture, int id)
/*Activate texture*/
{
    gl.glActiveTexture(texture);

    gl.glBindTexture(GL_TEXTURE_2D, this->texture);

    gl.glUniform1i(gl.glGetUniformLocation(shaderProgram, textureUniformName), id);
}

void TextureLoader::GenereteTexture(QOpenGLFunctions_3_3_Core &gl)
/*Create texture*/
{
    gl.glGenTextures(1, &texture);
    gl.glBindTexture(GL_TEXTURE_2D, texture);
    // Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void TextureLoader::LoadTexture(QOpenGLFunctions_3_3_Core &gl, const char *textureFileName)
/*Load texture*/
{
    QImage image(textureFileName);

    QImage tmpImage = QGLWidget::convertToGLFormat(image);

    gl.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tmpImage.width(), tmpImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tmpImage.bits());
    gl.glGenerateMipmap(GL_TEXTURE_2D);
}
void TextureLoader::CreateTexture(QOpenGLFunctions_3_3_Core &gl, const char *textureFileNmae)
/*Create texture*/
{
    GenereteTexture(gl);
    LoadTexture(gl, textureFileNmae);
}
}
