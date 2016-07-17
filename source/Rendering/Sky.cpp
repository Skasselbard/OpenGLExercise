//
// Created by tom on 15.07.16.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Sky.h"

Sky::Sky() : Sphere(80){
    viewMatrix = new mat4(1.0f);
    //createColorVertices();
    scale(-1.0f,1.0f,1.0f);
}

std::vector<vec4> Sky::createColorVertices() {
    std::vector<vec4> colorArray;
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
    return colorArray;
}

std::vector<glm::vec4> Sky::colorSubVertices(std::vector<glm::vec4> triangle, int iterations) {
    std::vector<glm::vec4> subColors = triangle;
    if (iterations > 0) {
        if (triangle.size() != 3) {
            assert(false);
        }
        iterations--;
        const glm::vec4 topColor = triangle[0];
        const glm::vec4 bottomColor = triangle[1];
        const glm::vec4 middleColor = (topColor + bottomColor) / 2;

        std::vector<glm::vec4> topTriangle;
        std::vector<glm::vec4> leftAndRigthTriangle;
        std::vector<glm::vec4> middleTriangle;

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

        topTriangle = colorSubVertices(topTriangle, iterations);
        leftAndRigthTriangle = colorSubVertices(leftAndRigthTriangle, iterations);
        middleTriangle = colorSubVertices(middleTriangle, iterations);

        subColors.insert(subColors.end(), topTriangle.begin(), topTriangle.end());
        subColors.insert(subColors.end(), leftAndRigthTriangle.begin(), leftAndRigthTriangle.end());
        subColors.insert(subColors.end(), middleTriangle.begin(), middleTriangle.end());
        subColors.insert(subColors.end(), leftAndRigthTriangle.begin(), leftAndRigthTriangle.end());
    }
    return subColors;
}

void Sky::calculateViewMatrix(glm::vec3 looktat, glm::vec3 eye) {
    *viewMatrix = glm::lookAt(
            glm::vec3(0,0,0),
            looktat-eye,
            glm::vec3((float)0.0,(float)1.0,(float)0.0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
}

void Sky::draw() {
    glUseProgram(shaderProgramID);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    GLint uniformLocation(0);
    uniformLocation = glGetUniformLocation(shaderProgramID, "viewMatrix");
    glUniformMatrix4fv(uniformLocation, 1, false, &(*viewMatrix)[0][0]);
    uniformLocation = glGetUniformLocation(shaderProgramID, "projectionMatrix");
    glUniformMatrix4fv(uniformLocation, 1, false, &(*projectionMatrix)[0][0]);
    glUseProgram(0);
    Drawable::draw();
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
}
















