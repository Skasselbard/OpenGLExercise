//
// Created by tom on 13.07.16.
//

#include <glm/gtx/transform.hpp>
#include "Drawable.h"

void Drawable::draw() {
    glUseProgram(shaderProgramID);
    GLint uniformLocation(0);
    uniformLocation = glGetUniformLocation(shaderProgramID, "modelMatrix");
    glUniformMatrix4fv(uniformLocation, 1, false, &(*modelMatrix)[0][0]);
    uniformLocation = glGetUniformLocation(shaderProgramID, "viewMatrix");
    glUniformMatrix4fv(uniformLocation, 1, false, &(*viewMatrix)[0][0]);
    uniformLocation = glGetUniformLocation(shaderProgramID, "projectionMatrix");
    glUniformMatrix4fv(uniformLocation, 1, false, &(*projectionMatrix)[0][0]);
    glBindVertexArray(vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, positionVertexCount);
    glBindVertexArray(0);
    glUseProgram(0);}

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

}

void Drawable::setViewMatrix(mat4 *matrix) {
    viewMatrix = matrix;
}

void Drawable::setModelMatrix(mat4 *matrix) {
    modelMatrix = matrix;
}

Drawable::Drawable() {
    modelMatrix = new mat4(1.0f);
}

void Drawable::createGeometry() {
    //create an empty list of vertices
    std::vector<vec3> vertexArray = createPositionVertices();
    positionVertexCount = vertexArray.size();
    //vertex array object -- wraps up geometry and consists of multiple vertex buffer objects and their stats
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    //create vertex buffer object -- a list of vertices, normals etc. In this case wraps up list of vertices. It exists on GPU side and allows transferring geometry data from CPU to GPU
    GLuint vboVertex;
    glGenBuffers(1, &vboVertex);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertex);
    //transfer vertices
    //void glBufferData(GLenum  target, GLsizeiptr  size, const GLvoid *  data, GLenum  usage);
    glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(vec3), vertexArray.data(), GL_STATIC_DRAW);
    //get attribute index for variable vsPosition
    GLint attributeIndex = glGetAttribLocation(shaderProgramID, "vsPosition");
    //tell GPU how to interpret this data for the specified attribute
    glVertexAttribPointer(attributeIndex, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    //activate this attribute
    glEnableVertexAttribArray(attributeIndex);
    //unbind vbo -- saves all stats given to this objects until this point
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //create empty list of color attributes
    std::vector<vec4> color = crerateColorVertices();
    //create another vertex buffer object -- a list of color attributes for each vertex. Must have the same number of elements, as the vertex list
    GLuint vboColor;
    glGenBuffers(1, &vboColor);
    glBindBuffer(GL_ARRAY_BUFFER, vboColor);
    //transfer color attributes
    glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(vec4), color.data(), GL_STATIC_DRAW);
    //get attribute index for variable vsPosition
    attributeIndex = glGetAttribLocation(shaderProgramID, "vsColor");
    //tell GPU how to interpret this data for the specified attribute
    glVertexAttribPointer(attributeIndex, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    //activate this attribute
    glEnableVertexAttribArray(attributeIndex);
    //unbind vertex array objects -- saves all stats given to this objects until this point
    glBindVertexArray(0);
    vertexArray.clear();
    color.clear();
}

void Drawable::setColor(glm::vec4 color) {

}


























