//
// Created by tom on 15.07.16.
//

#include <assert.h>
#include "ShaderCompiler.h"
#include <iostream>

const std::string ShaderCompiler::linkerTopic = "Link Program";
const std::string ShaderCompiler::validateTopic = "Validate Program";

char * ShaderCompiler::loadShaderFile(std::string const &file) {
//Helper methods
//Helper function to read text file

    FILE *fp = nullptr;
    char *content = nullptr;

    size_t count = 0;

    if (file.c_str() != nullptr) {
        fp = fopen(file.c_str(), "r");

        if (fp != nullptr) {

            fseek(fp, 0, SEEK_END);
            count = ftell(fp);
            rewind(fp);

            if (count > 0) {
                content = (char *)malloc(sizeof(char)* (count + 1));
                if (content != 0) {
                    count = fread(content, sizeof(char), count, fp);
                    content[count] = '\0';
                }
            }
            fclose(fp);
        }
    }
    return content;
}

GLint ShaderCompiler::buildShader(std::string file, SHADER_TYPE shaderType) {
//Vertex Shader-------------------------------------------------------
    // get a shader handler
    GLint shaderID;
    if (shaderType == VERTEX) {
        shaderID = glCreateShader(GL_VERTEX_SHADER);
    }else if ( shaderType == FRAGMENT){
        shaderID = glCreateShader(GL_FRAGMENT_SHADER);
    } else {
        return 0;
    }
    // read the shader source from a file
    char *shaderStream = nullptr;
    shaderStream = loadShaderFile(file);
    // conversions to fit the next function
    const char *  constShaderStream = shaderStream;
    // pass the source text to GL
    glShaderSource(shaderID, 1, &constShaderStream, NULL);
    // free the memory from the source text
    free(shaderStream);
    shaderStream = nullptr;
    // finally compile the shader
    glCompileShader(shaderID);
    //query status
    int query;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &query);
    if (!CheckQuery(query, shaderID, std::string("Shader " + schaderTypeToString(shaderType)))) return 0;
    return shaderID;
}

GLint ShaderCompiler::linkShader(GLint vertexShaderID, GLint fragmentShaderID) {
    GLint shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShaderID);
    glAttachShader(shaderProgramID, fragmentShaderID);
    glLinkProgram(shaderProgramID);
    int query;
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &query);
    if (!CheckQuery(query, shaderProgramID, std::string(linkerTopic))) return -1;
    glValidateProgram(shaderProgramID);
    glGetProgramiv(shaderProgramID, GL_VALIDATE_STATUS, &query);
    if (!CheckQuery(query, shaderProgramID, std::string(validateTopic))) return -1;
    return shaderProgramID;
}

bool ShaderCompiler::CheckQuery(int const & query, int const & id, std::string const & topic)
{
    //query status
    if (query == GL_FALSE) {
        std::string result;
        std::cout << "----------" << topic << "------------------- " << std::endl;
        if (topic != linkerTopic && topic != validateTopic) {
            result = PrintShaderInfoLog(id);
        }else{
            result = PrintProgramInfoLog(id);
        }
        std::string caption = "Error in " + std::string(topic.begin(), topic.end()) + ":";
        result = "Error in " + std::string(topic.begin(), topic.end()) + ":\n" + result + "\n" + "Application is closed.";
        printf("%s", result.c_str());
        assert(false); //shader could not be compiled- look at console for more infos
        return false;
    }

    return true;
}

std::string ShaderCompiler::PrintProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten = 0;
    char *infoLog;
    std::string result = "";

    glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n", infoLog);
        std::string s(infoLog);
        result = std::string(s.begin(), s.end());
        free(infoLog);
    }
    return result;
}

//debugs shader
std::string ShaderCompiler::PrintShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten = 0;
    char *infoLog;

    glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

    std::string result;

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
        std::string s(infoLog);
        result = std::string(s.begin(), s.end());
        printf("%s\n", infoLog);
        free(infoLog);
    }

    return result;
}

GLint ShaderCompiler::compileShader(std::string const vertexShaderFile, std::string const fragmentShaderFile) {
    if(vertexShaderFile == "" || fragmentShaderFile == ""){
        assert(false);
    }
    GLint vertexHandle = buildShader(vertexShaderFile,VERTEX);
    GLint fragmentHandle = buildShader(fragmentShaderFile,FRAGMENT);
    if (vertexHandle == 0 || fragmentHandle == 0){
        assert(false);
    }
    linkShader(vertexHandle, fragmentHandle);
}

std::string ShaderCompiler::schaderTypeToString(SHADER_TYPE type) {
    switch (type){
        case VERTEX: return "VertexShader";
        case FRAGMENT: return "FragmentShader";
        default: return "Unknown shader type";
    }
}

