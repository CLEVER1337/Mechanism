#include "ShaderProgram.h"

namespace nsGraphicsEngine
{
ShaderProgram::ShaderProgram()
{
}

ShaderProgram::ShaderProgram(QOpenGLFunctions_3_3_Core &gl, const char* vertexShaderFileName, const char* fragmentShaderFileName)
/*Create shaders and shader program*/
{
    CreateShaderProgram(gl, vertexShaderFileName, fragmentShaderFileName);
}

void ShaderProgram::CreateShaderProgram(QOpenGLFunctions_3_3_Core &gl, const char* vertexShaderFileName, const char* fragmentShaderFileName)
/*Create shaders and shader program*/
{
    BuildVertexShader(gl, vertexShaderFileName);
    BuildFragmentShader(gl, fragmentShaderFileName);
    LinkShaderProgram(gl);
    DeleteShaders(gl);
}

const char* ShaderProgram::ReadVertexShader(const char* shaderFileName)
/*Read vertex shader from file*/
{
    QFile file(shaderFileName);

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    if(file.isOpen())
    {
        QString str = file.readAll();

        file.close();

        return str.toStdString().c_str();
    }
    else
    {
        qDebug() << "Shader file " << shaderFileName << " hasn't opened\n";
    }

    file.close();

    return nullptr;
}

const char* ShaderProgram::ReadFragmentShader(const char* shaderFileName)
/*Read fragment shader from file*/
{
    QFile file(shaderFileName);

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    if(file.isOpen())
    {
        QString str = file.readAll();

        file.close();

        return str.toStdString().c_str();
    }
    else
    {
        qDebug() << "Shader file " << shaderFileName << " hasn't opened\n";
    }

    file.close();

    return nullptr;
}

void ShaderProgram::BuildVertexShader(QOpenGLFunctions_3_3_Core &gl, const char* shaderFileName)
/*Build vertex shader*/
{
    const char* const vertexShaderStr = ReadVertexShader(shaderFileName);

    vertexShader = gl.glCreateShader(GL_VERTEX_SHADER);
    gl.glShaderSource(vertexShader, 1, &vertexShaderStr, NULL);
    gl.glCompileShader(vertexShader);
}

void ShaderProgram::BuildFragmentShader(QOpenGLFunctions_3_3_Core &gl, const char* shaderFileName)
/*Build fragment shader*/
{
    const char* const fragmentShaderStr = ReadFragmentShader(shaderFileName);

    fragmentShader = gl.glCreateShader(GL_FRAGMENT_SHADER);
    gl.glShaderSource(fragmentShader, 1, &fragmentShaderStr, NULL);
    gl.glCompileShader(fragmentShader);
}

void ShaderProgram::LinkShaderProgram(QOpenGLFunctions_3_3_Core &gl)
/*Link shader program*/
{
    shaderProgram = gl.glCreateProgram();

    gl.glAttachShader(shaderProgram, vertexShader);
    gl.glAttachShader(shaderProgram, fragmentShader);
    gl.glLinkProgram(shaderProgram);
}

void ShaderProgram::DeleteShaders(QOpenGLFunctions_3_3_Core &gl)
/*Delete shaders*/
{
    gl.glDeleteShader(vertexShader);
    gl.glDeleteShader(fragmentShader);
}

void ShaderProgram::UseShaderProgram(QOpenGLFunctions_3_3_Core &gl)
/*Use shader program*/
{
    gl.glUseProgram(shaderProgram);
}

GLuint ShaderProgram::GetShaderProgram()
/*Getter for shader program*/
{
    return shaderProgram;
}

void ShaderProgram::SetInt(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, int uniformValue)
{
    GLint location = gl.glGetUniformLocation(shaderProgram, uniformName);
    gl.glUniform1i(location, uniformValue);
}

void ShaderProgram::SetFloat(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, float uniformValue)
{
    GLint location = gl.glGetUniformLocation(shaderProgram, uniformName);
    gl.glUniform1f(location, uniformValue);
}

void ShaderProgram::SetVec2(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, glm::vec2 uniformValue)
{
    GLint location = gl.glGetUniformLocation(shaderProgram, uniformName);
    gl.glUniform2f(location, uniformValue.x, uniformValue.y);
}

void ShaderProgram::SetVec2(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, float x, float y)
{
    GLint location = gl.glGetUniformLocation(shaderProgram, uniformName);
    gl.glUniform2f(location, x, y);
}

void ShaderProgram::SetVec3(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, glm::vec3 uniformValue)
{
    GLint location = gl.glGetUniformLocation(shaderProgram, uniformName);
    gl.glUniform3f(location, uniformValue.x, uniformValue.y, uniformValue.z);
}

void ShaderProgram::SetVec3(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, float x, float y, float z)
{
    GLint location = gl.glGetUniformLocation(shaderProgram, uniformName);
    gl.glUniform3f(location, x, y, z);
}

void ShaderProgram::SetVec4(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, glm::vec4 uniformValue)
{
    GLint location = gl.glGetUniformLocation(shaderProgram, uniformName);
    gl.glUniform4f(location, uniformValue.x, uniformValue.y, uniformValue.z, uniformValue.w);
}

void ShaderProgram::SetVec4(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, float x, float y, float z, float w)
{
    GLint location = gl.glGetUniformLocation(shaderProgram, uniformName);
    gl.glUniform4f(location, x, y, z, w);
}

void ShaderProgram::SetMat2(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, glm::mat2 uniformValue)
{
    GLint location = gl.glGetUniformLocation(shaderProgram, uniformName);
    gl.glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(uniformValue));
}

void ShaderProgram::SetMat3(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, glm::mat3 uniformValue)
{
    GLint location = gl.glGetUniformLocation(shaderProgram, uniformName);
    gl.glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(uniformValue));
}

void ShaderProgram::SetMat4(QOpenGLFunctions_3_3_Core &gl, const char* uniformName, glm::mat4 uniformValue)
{
    GLint location = gl.glGetUniformLocation(shaderProgram, uniformName);
    gl.glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(uniformValue));
}
}
