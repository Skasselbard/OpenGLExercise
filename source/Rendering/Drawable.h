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
    void setModelMatrix(mat4 *matrix);
    void setViewMatrix(mat4 *matrix);
    void setProjectionMatrix(mat4 *matrix);


protected:
    GLint shaderProgramID = 0;
    GLuint vertexArrayObject = 0;
    glm::mat4 *viewMatrix = nullptr;
    glm::mat4 *modelMatrix = nullptr;
    glm::mat4 *projectionMatrix = nullptr;


    virtual void createGeometry()=0;
};


#endif //AUFGABE_DRAWABLE_H
