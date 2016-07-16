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
    virtual std::string className()=0;


protected:
    GLint shaderProgramID = 0;
    GLuint vertexArrayObject = 0;
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    virtual void createGeometry()=0;
};


#endif //AUFGABE_DRAWABLE_H
