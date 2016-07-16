//
// Created by tom on 13.07.16.
//

#ifndef AUFGABE_DRAWABLE_H
#define AUFGABE_DRAWABLE_H

#include "Precompiled.h"
class Drawable {
public:
    Drawable();
    virtual void draw();
    void scale(float x, float y, float z);
    void scale(float xyz);
    virtual void translate(float x, float y, float z);
    void setShaderProgramm(GLint ShaderProgramID);
    void setModelMatrix(mat4 *matrix);
    void setViewMatrix(mat4 *matrix);
    void setProjectionMatrix(mat4 *matrix);
    void setColor(glm::vec4 color);


protected:
    GLint shaderProgramID = 0;
    GLuint vertexArrayObject = 0;
    GLuint positionVertexCount = 0;
    glm::mat4 *viewMatrix = nullptr;
    glm::mat4 *modelMatrix = nullptr;
    glm::mat4 *projectionMatrix = nullptr;

    virtual std::vector<vec3> createPositionVertices()=0;
    virtual std::vector<vec4> crerateColorVertices()=0;
    virtual std::vector<vec4> crerateColorVertices(glm::vec4 color)=0;

private:
    void createGeometry();
};


#endif //AUFGABE_DRAWABLE_H
