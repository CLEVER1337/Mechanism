#include <QDebug>
#include <QString>
#include <QFile>

#include "ShaderProgram.h"

namespace nsUtility
{
ShaderProgram::ShaderProgram()
{
}

ShaderProgram::ShaderProgram(QOpenGLFunctions_3_3_Core &gl, const char* vertexShaderFileName, const char* fragmentShaderFileName)
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

        //vertexShaderStr.resize(str.size());

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

        //fragmentShaderStr.resize(str.size());

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
}
