//
// Created by tom on 13.07.16.
//

#include <glm/gtx/transform.hpp>
#include "Drawable.h"

char * Drawable::loadShaderFile(std::string const &file) {
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

GLint Drawable::buildShader(std::string file, SHADER_TYPE shaderType) {
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
    if (!CheckQuery(query, shaderID, std::string("Shader"))) return 0;
    return shaderID;
}

bool Drawable::CheckQuery(int const & query, int const & id, std::string const & topic)
{
    //query status
    if (query == GL_FALSE) {
        std::cout << "----------" << topic << "------------------- " << std::endl;
        std::string result = PrintShaderInfoLog(id);

        std::string caption = "Error in " + std::string(topic.begin(), topic.end()) + ":";

        result = "Error in " + std::string(topic.begin(), topic.end()) + ":\n" + result + "\n" + "Application is closed.";

        //this is a windows method. If compiled with a different operating system, comment/replace this method
        //MessageBox(NULL, result.c_str(), caption.c_str(), MB_ICONEXCLAMATION | MB_ICONWARNING);
        //
        // tom: wstrings are bad with stdout. Quickest fix is to to use std::string
        printf("%s", result.c_str());

        assert(false); //shader could not be compiled- look at console for more infos
        return false;
    }

    return true;
}

void Drawable::PrintProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten = 0;
    char *infoLog;

    glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n", infoLog);
        free(infoLog);
    }
}

//debugs shader
std::string Drawable::PrintShaderInfoLog(GLuint obj)
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

void Drawable::linkShader(GLint vertexShaderID, GLint fragmentShaderID) {
    shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShaderID);
    glAttachShader(shaderProgramID, fragmentShaderID);
    glLinkProgram(shaderProgramID);
    int query;
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &query);
    if (!CheckQuery(query, shaderProgramID, std::string("Link Program"))) return;
    glValidateProgram(shaderProgramID);
    glGetProgramiv(shaderProgramID, GL_VALIDATE_STATUS, &query);
    if (!CheckQuery(query, shaderProgramID, std::string("Validate Program"))) return;
}

void Drawable::setFragmentShaderFile(std::string const &file) {
    fragmentShaderFile = file;
}

void Drawable::setVertexShaderFile(std::string const &file) {
    vertexShaderFile = file;
}

void Drawable::initShader() {
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

void Drawable::draw() {
    assert(false);
}

void Drawable::scale(float x, float y, float z) {
    modelMatrix = glm::scale(modelMatrix, glm::vec3(x,y,z));
}

void Drawable::translate(float x, float y, float z) {
    modelMatrix = glm::translate(modelMatrix, glm::vec3(x,y,z));
}

void Drawable::setShaderProgramm(GLint shaderProgramID) {
    this->shaderProgramID = shaderProgramID;
}









