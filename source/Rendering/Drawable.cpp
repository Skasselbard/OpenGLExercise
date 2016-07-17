//
// Created by tom on 13.07.16.
//

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "Drawable.h"

void Drawable::draw() {
    /*LightInfo lightInfo;
    lightInfo.Ambient = vec3(0.5,0.5,0.5);
    lightInfo.Diffuse = vec3(0.9,0.5,0.3);
    lightInfo.Specular = vec3(0.5,0.5,0.5);
    lightInfo.Position = vec3(-10,40,10);
    LightInfo light[1];
    light[0] = lightInfo;
    MaterialInfo material;
    material.Specular = vec3(0.5,0.5,0.5);
    material.Diffuse = vec3(0.5,0.5,0.5);
    material.Ambient = vec3(0.5,0.5,0.5);
    material.Shininess = 1.0f;*/

    mat3 normalMatrix = glm::inverseTranspose(mat3((*viewMatrix) * (*modelMatrix)));
    glUseProgram(shaderProgramID);
    GLint uniformLocation(0);
    uniformLocation = glGetUniformLocation(shaderProgramID, "modelMatrix");
    glUniformMatrix4fv(uniformLocation, 1, false, &(*modelMatrix)[0][0]);
    uniformLocation = glGetUniformLocation(shaderProgramID, "viewMatrix");
    glUniformMatrix4fv(uniformLocation, 1, false, &(*viewMatrix)[0][0]);
    uniformLocation = glGetUniformLocation(shaderProgramID, "projectionMatrix");
    glUniformMatrix4fv(uniformLocation, 1, false, &(*projectionMatrix)[0][0]);
    uniformLocation = glGetUniformLocation(shaderProgramID, "normalMatrix");
    glUniformMatrix3fv(uniformLocation, 1, false, &normalMatrix[0][0]);
    /*
    uniformLocation = glGetUniformLocation(shaderProgramID, "Light");
    glUniform(uniformLocation, 1, false, &light);
    uniformLocation = glGetUniformLocation(shaderProgramID, "Material");
    glUniformMatrix4fv(uniformLocation, 1, false, &material);
    */
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
    this->setupGeometry();
    std::vector<vec4> colorVertices = this->createColorVertices();
    this->setupSurface(colorVertices);
    this->setupNormals();
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

void Drawable::setupGeometry() {
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
    glBindVertexArray(0);
    vertexArray.clear();
}

void Drawable::setColor(glm::vec4 color) {
    glDeleteVertexArrays(1,&vertexArrayObject);
    *modelMatrix = mat4(1.0f); //reset modelmatrix because of scaling that takes place in some subclasses
    setupGeometry();
    std::vector<vec4> colorVertices = createColorVertices(color);
    setupSurface(colorVertices);
    setupNormals();
}

void Drawable::setupSurface(std::vector<vec4> &colorVertices) {
    glBindVertexArray(vertexArrayObject);
    //create another vertex buffer object -- a list of color attributes for each vertex. Must have the same number of elements, as the vertex list
    GLuint vboColor;
    glGenBuffers(1, &vboColor);
    glBindBuffer(GL_ARRAY_BUFFER, vboColor);
    //transfer color attributes
    glBufferData(GL_ARRAY_BUFFER, colorVertices.size() * sizeof(vec4), colorVertices.data(), GL_STATIC_DRAW);
    //get attribute index for variable vsPosition
    GLint attributeIndex = glGetAttribLocation(shaderProgramID, "vsColor");
    //tell GPU how to interpret this data for the specified attribute
    glVertexAttribPointer(attributeIndex, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    //activate this attribute
    glEnableVertexAttribArray(attributeIndex);
    //unbind vertex array objects -- saves all stats given to this objects until this point
    glBindVertexArray(0);
    colorVertices.clear();
}

std::vector<vec3> Drawable::createNormalVertices() {
    std::vector<vec3> normalArray = createPositionVertices();
    if (normalArray.size()%3 != 0){
        assert(false);
    }
    for (size_t i = 2; i<normalArray.size(); i+=3){
        vec3 ab = normalArray[i-1] - normalArray[i-2];
        vec3 bc = normalArray[i] - normalArray[i-2];
        vec3 normal = glm::cross(ab,bc);
        for(int j=0; j<3; j++){
            normalArray[i+j-2]=glm::normalize(normal);
        }
    }
    return normalArray;
}

void Drawable::setupNormals() {
    std::vector<vec3> normals = createNormalVertices();
    glBindVertexArray(vertexArrayObject);
    //create another vertex buffer object -- a list of color attributes for each vertex. Must have the same number of elements, as the vertex list
    GLuint vboNormals;
    glGenBuffers(1, &vboNormals);
    glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
    //transfer color attributes
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), normals.data(), GL_STATIC_DRAW);
    //get attribute index for variable vsPosition
    GLint attributeIndex = glGetAttribLocation(shaderProgramID, "vsNormal");
    //tell GPU how to interpret this data for the specified attribute
    glVertexAttribPointer(attributeIndex, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    //activate this attribute
    glEnableVertexAttribArray(attributeIndex);
    //unbind vertex array objects -- saves all stats given to this objects until this point
    glBindVertexArray(0);
    normals.clear();
}
































