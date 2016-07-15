//
// Created by tom on 15.07.16.
//

#ifndef AUFGABE_SHADERCOMPILER_H
#define AUFGABE_SHADERCOMPILER_H

#include <GL/glew.h>
#include "Precompiled.h"
#include <string>

class ShaderCompiler {
public:
    static GLint compileShader(std::string const vertexShaderFile, std::string const fragmentShaderFile);

private:
    enum SHADER_TYPE{
        VERTEX,
        FRAGMENT
    };
    static const std::string linkerTopic;
    static const std::string validateTopic;
    static char * loadShaderFile(std::string const &file);
    static GLint buildShader(std::string file, SHADER_TYPE shaderType);
    static GLint linkShader(GLint vertexShaderID, GLint fragmentShaderID);

    static bool CheckQuery(const int &query, const int &id, const std::string &topic);
    static std::string PrintProgramInfoLog(GLuint obj);
    static std::string PrintShaderInfoLog(GLuint obj);

    static std::string schaderTypeToString(SHADER_TYPE type);
};


#endif //AUFGABE_SHADERCOMPILER_H
