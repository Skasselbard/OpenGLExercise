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
    void translate(float x, float y, float z);
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
    virtual std::vector<vec4> createColorVertices()=0;
    virtual std::vector<vec4> createColorVertices(glm::vec4 color)=0;
    virtual std::vector<vec3> createNormalVertices();

private:
    struct LightInfo{
        vec3 Position;	//Light Position in eye-coords
        vec3 Ambient;		//Ambient light intensity
        vec3 Diffuse;		//Diffuse light intensity
        vec3 Specular;		//Specular light intensity
    };

    struct MaterialInfo{
        vec3 Ambient;			//Ambient reflectivity
        vec3 Diffuse;			//Diffuse reflectivity
        vec3 Specular;			//Specular reflectivity
        float Shininess;	//Specular shininess factor
    };

    void setupGeometry();
    void setupSurface(std::vector<vec4> &colorVertices);
    void setupNormals();
};


#endif //AUFGABE_DRAWABLE_H
