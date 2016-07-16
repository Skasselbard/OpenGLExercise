//
// Created by tom on 15.07.16.
//

#include "Sky.h"

Sky::Sky() : Sphere(1){
    addColorVertices();
    //colorize();
    scale(-1.0f,1.0f,1.0f);
}

void Sky::addColorVertices() {
    const float grayFactor = 0.8f;
    const glm::vec4 topColor = glm::vec4(grayFactor,grayFactor,1.0f,1.0f);
    const glm::vec4 middleColor = glm::vec4(0.0f,0.0f,1.0f,1.0f);
    const glm::vec4 bottomColor = glm::vec4(0.0f,0.0f,1.0f/2,1.0f);

    for (int i = 0; i<4; i++){//Top 4 surfaces
        std::vector<vec4> triangle;
        triangle.push_back(topColor);
        triangle.push_back(middleColor);
        triangle.push_back(middleColor);
        triangle = colorSubVertices(triangle, detailIterations);
        colorArray.insert(colorArray.end(), triangle.begin(), triangle.end());
    }
    for (int i = 0; i<4; i++){//Bottom 4 surfaces
        std::vector<vec4> triangle;
        triangle.push_back(bottomColor);
        triangle.push_back(middleColor);
        triangle.push_back(middleColor);
        triangle = colorSubVertices(triangle, detailIterations);
        colorArray.insert(colorArray.end(), triangle.begin(), triangle.end());
    }
}

std::vector<glm::vec4> Sky::colorSubVertices(std::vector<glm::vec4> triangle, int iterations) {
    if(triangle.size() != 3){
        assert(false);
    }
    const glm::vec4 topColor = triangle[0];
    const glm::vec4 bottomColor = triangle[1];
    const glm::vec4 middleColor = (topColor+bottomColor)/2;

    std::vector<glm::vec4> topTriangle;
    std::vector<glm::vec4> leftAndRigthTriangle;
    std::vector<glm::vec4> middleTriangle;
    std::vector<glm::vec4> subColors;

    //Top Triangle
    topTriangle.push_back(topColor);
    topTriangle.push_back(middleColor);
    topTriangle.push_back(middleColor);
    //LeftAndRight Triangle
    leftAndRigthTriangle.push_back(middleColor);
    leftAndRigthTriangle.push_back(bottomColor);
    leftAndRigthTriangle.push_back(bottomColor);
    //Middle Triangle
    middleTriangle.push_back(bottomColor);
    middleTriangle.push_back(middleColor);
    middleTriangle.push_back(middleColor);


    if (iterations > 0){
        iterations--;
        topTriangle = colorSubVertices(topTriangle, iterations);
        leftAndRigthTriangle = colorSubVertices(leftAndRigthTriangle, iterations);
        middleTriangle = colorSubVertices(middleTriangle, iterations);

    }
    subColors.insert(subColors.end(), topTriangle.begin(), topTriangle.end());
    subColors.insert(subColors.end(), leftAndRigthTriangle.begin(), leftAndRigthTriangle.end());
    subColors.insert(subColors.end(), middleTriangle.begin(), middleTriangle.end());
    subColors.insert(subColors.end(), leftAndRigthTriangle.begin(), leftAndRigthTriangle.end());

    return subColors;
}

void Sky::colorize() {
    glBindVertexArray(vertexArrayObject);
    //create another vertex buffer object -- a list of color attributes for each vertex. Must have the same number of elements, as the vertex list
    GLuint vboColor;
    glGenBuffers(1, &vboColor);
    glBindBuffer(GL_ARRAY_BUFFER, vboColor);
    //transfer color attributes
    glBufferData(GL_ARRAY_BUFFER, colorArray.size() * sizeof(vec4), colorArray.data(), GL_STATIC_DRAW);
    //get attribute index for variable vsPosition
    GLint attributeIndex = glGetAttribLocation(shaderProgramID, "vsColor");
    //tell GPU how to interpret this data for the specified attribute
    glVertexAttribPointer(attributeIndex, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    //activate this attribute
    glEnableVertexAttribArray(attributeIndex);
    //unbind vertex array objects -- saves all stats given to this objects until this point
    glBindVertexArray(0);
}

void Sky::createGeometry() {
    addVertices(vertexArray);
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
    //unbind vertex array objects -- saves all stats given to this objects until this point
    GLuint vboColor;
    glGenBuffers(1, &vboColor);
    glBindBuffer(GL_ARRAY_BUFFER, vboColor);
    //transfer color attributes
    glBufferData(GL_ARRAY_BUFFER, colorArray.size() * sizeof(vec4), colorArray.data(), GL_STATIC_DRAW);
    //get attribute index for variable vsPosition
    attributeIndex = glGetAttribLocation(shaderProgramID, "vsColor");
    //tell GPU how to interpret this data for the specified attribute
    glVertexAttribPointer(attributeIndex, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    //activate this attribute
    glEnableVertexAttribArray(attributeIndex);
    //unbind vertex array objects -- saves all stats given to this objects until this point
    glBindVertexArray(0);
}












