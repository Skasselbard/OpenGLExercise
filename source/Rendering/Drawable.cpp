//
// Created by tom on 13.07.16.
//

#include <glm/gtx/transform.hpp>
#include "Drawable.h"

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
    this->createGeometry();
}

void Drawable::scale(float xyz) {
    modelMatrix = glm::scale(modelMatrix, glm::vec3(xyz,xyz,xyz));
}














