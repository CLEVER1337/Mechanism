#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <QGLFunctions>
#include <QOpenGLFunctions_3_3_Core>



namespace nsUtility
{
/*!
 * \class ShaderProgram
 * \brief This class creating shaders and shader program
*/
class ShaderProgram
{
public:
    ShaderProgram();
    /*!
     * \fn ShaderProgram(QOpenGLFunctions_3_3_Core &gl, const char* vertexShaderFileName, const char* fragmentShaderFileName)
     * \brief This constructor creating shaders and shader program
    */
    ShaderProgram(QOpenGLFunctions_3_3_Core &gl, const char* vertexShaderFileName, const char* fragmentShaderFileName);
    /*!
     * \fn void CreateShaderProgram(QOpenGLFunctions_3_3_Core &gl, const char* vertexShaderFileName, const char* fragmentShaderFileName)
     * \brief This function using shader program
    */
    void CreateShaderProgram(QOpenGLFunctions_3_3_Core &gl, const char* vertexShaderFileName, const char* fragmentShaderFileName);
    /*!
     * \fn void UseShaderProgram(QOpenGLFunctions_3_3_Core &gl)
     * \brief This function using shader program
    */
    void UseShaderProgram(QOpenGLFunctions_3_3_Core &gl);
    /*!
     * \fn GLuint GetShaderProgram()
     * \brief Getter for shader program
    */
    GLuint GetShaderProgram();

private:
    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;

    const char* ReadVertexShader(const char* shaderFileName);

    const char* ReadFragmentShader(const char* shaderFileName);

    void BuildVertexShader(QOpenGLFunctions_3_3_Core &gl, const char* shaderFileName);

    void BuildFragmentShader(QOpenGLFunctions_3_3_Core &gl, const char* shaderFileName);

    void LinkShaderProgram(QOpenGLFunctions_3_3_Core &gl);

    void DeleteShaders(QOpenGLFunctions_3_3_Core &gl);
};
}

#endif // SHADERPROGRAM_H
