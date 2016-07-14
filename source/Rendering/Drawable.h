//
// Created by tom on 13.07.16.
//

#ifndef AUFGABE_DRAWABLE_H
#define AUFGABE_DRAWABLE_H

#include "Precompiled.h"
class Drawable {
public:

    virtual void draw() = 0;
    void scale(float x, float y, float z);
    void scale(float xyz);
    virtual void translate(float x, float y, float z);
    void setShaderProgramm(GLint ShaderProgramID);


protected:
    GLint shaderProgramID = 0;
    GLuint vertexArrayObject = 0;
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    void setFragmentShaderFile(std::string const &file);
    void setVertexShaderFile(std::string const &file);
    void initShader();
    virtual void createGeometry()=0;

private:
    enum SHADER_TYPE{
        VERTEX,
        FRAGMENT
    };
    std::string fragmentShaderFile = "";
    std::string vertexShaderFile = "";

    char * loadShaderFile(std::string const &file);
    GLint buildShader(std::string file, SHADER_TYPE shaderType);
    void linkShader(GLint vertexShaderID, GLint fragmentShaderID);

    bool CheckQuery(const int &query, const int &id, const std::string &topic);
    void PrintProgramInfoLog(GLuint obj);

    std::string PrintShaderInfoLog(GLuint obj);

};


#endif //AUFGABE_DRAWABLE_H
