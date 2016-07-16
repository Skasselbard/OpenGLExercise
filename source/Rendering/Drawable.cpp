//
// Created by tom on 13.07.16.
//

#include <glm/gtx/transform.hpp>
#include "Drawable.h"

void Drawable::draw() {
    assert(false);
}

void Drawable::scale(float x, float y, float z) {
    *modelMatrix = glm::scale(*modelMatrix, glm::vec3(x,y,z));
}

void Drawable::translate(float x, float y, float z) {
    *modelMatrix = glm::translate(*modelMatrix, glm::vec3(x,y,z));
}

void Drawable::setShaderProgramm(GLint shaderProgramID) {
    this->shaderProgramID = shaderProgramID;
    this->createGeometry();
}

void Drawable::scale(float xyz) {
    *modelMatrix = glm::scale(*modelMatrix, glm::vec3(xyz,xyz,xyz));
}

void Drawable::setProjectionMatrix(mat4 *matrix) {
    projectionMatrix = matrix;
    float aspectRatio = static_cast<float>(1000)/static_cast<float>(1000);
    projectionMatrix = new mat4(1.0f);

}

void Drawable::setViewMatrix(mat4 *matrix) {
    viewMatrix = matrix;
    //viewMatrix = new mat4(1.0f);
}

void Drawable::setModelMatrix(mat4 *matrix) {
    modelMatrix = matrix;
}




















