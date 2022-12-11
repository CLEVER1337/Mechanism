#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <QGLFunctions>
#include <QOpenGLFunctions_3_3_Core>
#include <QDebug>
#include <QString>
#include <QFile>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace nsUtility
{
/*!
 * \class ShaderProgram
 * \brief This class creating shaders and shader program
*/
class ShaderProgram
{
public:
    /*!
     * \fn ShaderProgram()
     * \brief Standard constructor
    */
    ShaderProgram();
    /*!
     * \fn ShaderProgram(QOpenGLFunctions_3_3_Core &gl, const char* vertexShaderFileName, const char* fragmentShaderFileName)
     * \brief This constructor creating shaders and shader program
    */
    ShaderProgram(QOpenGLFunctions_3_3_Core &gl, const char* vertexShaderFileName, const char* fragmentShaderFileName);

    /*!
     * \fn void CreateShaderProgram(QOpenGLFunctions_3_3_Core &gl, const char* vertexShaderFileName, const char* fragmentShaderFileName)
     * \brief This function creating shader program
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
     * Return: shader program id
    */
    GLuint GetShaderProgram();

    /*!
     * \fn void SetInt(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, bool uniformValue)
     * \brief This function set single int uniform
    */
    void SetInt(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, int uniformValue);
    /*!
     * \fn void SetFloat(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, float uniformValue)
     * \brief This function set single float uniform
    */
    void SetFloat(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, float uniformValue);
    /*!
     * \fn void SetVec2(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, glm::vec2 uniformValue)
     * \brief This function set double float uniform
    */
    void SetVec2(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, glm::vec2 uniformValue);
    /*!
     * \fn void SetVec2(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, glm::vec2 uniformValue)
     * \brief This function set double float uniform
    */
    void SetVec2(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, float x, float y);
    /*!
     * \fn void SetVec3(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, glm::vec3 uniformValue)
     * \brief This function set triple float uniform
    */
    void SetVec3(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, glm::vec3 uniformValue);
    /*!
     * \fn void SetVec3(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, float x, float y, float z)
     * \brief This function set triple float uniform
    */
    void SetVec3(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, float x, float y, float z);
    /*!
     * \fn void SetVec4(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, glm::vec4 uniformValue)
     * \brief This function set quadro float uniform
    */
    void SetVec4(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, glm::vec4 uniformValue);
    /*!
     * \fn void SetVec4(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, float x, float y, float z, float w)
     * \brief This function set quadro float uniform
    */
    void SetVec4(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, float x, float y, float z, float w);
    /*!
     * \fn void SetMat2(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, glm::mat2 uniformValue)
     * \brief This function set 2x2 matrix uniform
    */
    void SetMat2(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, glm::mat2 uniformValue);
    /*!
     * \fn void SetMat3(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, glm::mat3 uniformValue)
     * \brief This function set 3x3 matrix uniform
    */
    void SetMat3(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, glm::mat3 uniformValue);
    /*!
     * \fn void SetMat4(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, glm::mat4 uniformValue)
     * \brief This function set 4x4 matrix uniform
    */
    void SetMat4(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, glm::mat4 uniformValue);

private:
    /*!
     * \var GLuint shaderProgram
     * \brief Shader program
    */
    GLuint shaderProgram;
    /*!
     * \var GLuint vertexShader
     * \brief Vertex shader
    */
    GLuint vertexShader;
    /*!
     * \var GLuint fragmentShader
     * \brief Fragment shader
    */
    GLuint fragmentShader;

    /*!
     * \fn const char* ReadVertexShader(const char* shaderFileName)
     * \brief This function reading vertex sahder from file
     * Return: vertex shader in string
    */
    const char* ReadVertexShader(const char* shaderFileName);

    /*!
     * \fn const char* ReadFragmentShader(const char* shaderFileName)
     * \brief This function reading fragment sahder from file
     * Return: fragment shader in string
    */
    const char* ReadFragmentShader(const char* shaderFileName);

    /*!
     * \fn void BuildVertexShader(QOpenGLFunctions_3_3_Core &gl, const char* shaderFileName)
     * \brief This function building vertex shader
    */
    void BuildVertexShader(QOpenGLFunctions_3_3_Core &gl, const char* shaderFileName);

    /*!
     * \fn void BuildFragmentShader(QOpenGLFunctions_3_3_Core &gl, const char* shaderFileName)
     * \brief This function building fragment shader
    */
    void BuildFragmentShader(QOpenGLFunctions_3_3_Core &gl, const char* shaderFileName);

    /*!
     * \fn void LinkShaderProgram(QOpenGLFunctions_3_3_Core &gl)
     * \brief This function linking shader program
    */
    void LinkShaderProgram(QOpenGLFunctions_3_3_Core &gl);

    /*!
     * \fn void DeleteShaders(QOpenGLFunctions_3_3_Core &gl)
     * \brief This function deleting shaders
    */
    void DeleteShaders(QOpenGLFunctions_3_3_Core &gl);
};
}

#endif // SHADERPROGRAM_H
