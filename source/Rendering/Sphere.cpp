//
// Created by tom on 14.07.16.
//

#include <glm/gtx/transform.hpp>
#include "Sphere.h"

Sphere::Sphere(float radius) {
    this->radius=radius;
    modelMatrix = new mat4(1.0f);
}

std::vector<vec3> Sphere::createPositionVertices() {
    std::vector<vec3> vertexArray;

    //vertex positions
    const glm::vec3 top         = glm::vec3(0.0f,radius,0.0f);
    const glm::vec3 bottom      = glm::vec3(0.0f,-radius,0.0f);
    const glm::vec3 frontLeft   = glm::vec3(-radius,0.0f,radius);
    const glm::vec3 frontRight  = glm::vec3(radius,0.0f,radius);
    const glm::vec3 backLeft    = glm::vec3(-radius,0.0f,-radius);
    const glm::vec3 backRight   = glm::vec3(radius,0.0f,-radius);

    std::vector<vec3> vertexArrayTopFront;
    std::vector<vec3> vertexArrayTopLeft;
    std::vector<vec3> vertexArrayTopRight;
    std::vector<vec3> vertexArrayTopBack;
    std::vector<vec3> vertexArrayBottomFront;
    std::vector<vec3> vertexArrayBottomLeft;
    std::vector<vec3> vertexArrayBottomRight;
    std::vector<vec3> vertexArrayBottomBack;

    //add und split triangles
    //TopFront
    vertexArrayTopFront.push_back(top);
    vertexArrayTopFront.push_back(frontLeft);
    vertexArrayTopFront.push_back(frontRight);
    vertexArrayTopFront= splitTriangle(vertexArrayTopFront, detailIterations);

    //TopLeft
    vertexArrayTopLeft.push_back(top);
    vertexArrayTopLeft.push_back(backLeft);
    vertexArrayTopLeft.push_back(frontLeft);
    vertexArrayTopLeft= splitTriangle(vertexArrayTopLeft, detailIterations);

    //TopRight
    vertexArrayTopRight.push_back(top);
    vertexArrayTopRight.push_back(frontRight);
    vertexArrayTopRight.push_back(backRight);
    vertexArrayTopRight= splitTriangle(vertexArrayTopRight, detailIterations);
    //TopBack
    vertexArrayTopBack.push_back(top);
    vertexArrayTopBack.push_back(backRight);
    vertexArrayTopBack.push_back(backLeft);
    vertexArrayTopBack= splitTriangle(vertexArrayTopBack, detailIterations);
    //BottomFront
    vertexArrayBottomFront.push_back(bottom);
    vertexArrayBottomFront.push_back(frontRight);
    vertexArrayBottomFront.push_back(frontLeft);
    vertexArrayBottomFront= splitTriangle(vertexArrayBottomFront, detailIterations);
    //BottomLeft
    vertexArrayBottomLeft.push_back(bottom);
    vertexArrayBottomLeft.push_back(frontLeft);
    vertexArrayBottomLeft.push_back(backLeft);
    vertexArrayBottomLeft= splitTriangle(vertexArrayBottomLeft, detailIterations);
    //BottomRight
    vertexArrayBottomRight.push_back(bottom);
    vertexArrayBottomRight.push_back(backRight);
    vertexArrayBottomRight.push_back(frontRight);
    vertexArrayBottomRight= splitTriangle(vertexArrayBottomRight, detailIterations);
    //BottomBack
    vertexArrayBottomBack.push_back(bottom);
    vertexArrayBottomBack.push_back(backLeft);
    vertexArrayBottomBack.push_back(backRight);
    vertexArrayBottomBack= splitTriangle(vertexArrayBottomBack, detailIterations);


    vertexArray.insert(vertexArray.end(),vertexArrayTopFront.begin(), vertexArrayTopFront.end());
    vertexArray.insert(vertexArray.end(),vertexArrayTopLeft.begin(), vertexArrayTopLeft.end());
    vertexArray.insert(vertexArray.end(),vertexArrayTopRight.begin(), vertexArrayTopRight.end());
    vertexArray.insert(vertexArray.end(),vertexArrayTopBack.begin(), vertexArrayTopBack.end());
    vertexArray.insert(vertexArray.end(),vertexArrayBottomFront.begin(), vertexArrayBottomFront.end());
    vertexArray.insert(vertexArray.end(),vertexArrayBottomLeft.begin(), vertexArrayBottomLeft.end());
    vertexArray.insert(vertexArray.end(),vertexArrayBottomRight.begin(), vertexArrayBottomRight.end());
    vertexArray.insert(vertexArray.end(),vertexArrayBottomBack.begin(), vertexArrayBottomBack.end());

    const float scalefactor =128; // the higher, the rounder
    //Normalize vertices
    for (int i = 0; i < vertexArray.size(); i++){
        vertexArray[i] = normalize(vertexArray[i],glm::vec3(0.0f,0.0f,0.0f),-radius*scalefactor)/(scalefactor);
    }
    return vertexArray;
}
/**
 * from this nice post
 * //http://stackoverflow.com/a/7687312
 */
vec3 Sphere::normalize(vec3 fixpoint, vec3 point, float radius) {
        //get the distance between a and b along the x and y axes
    float dx = point.x - fixpoint.x;
    float dy = point.y - fixpoint.y;
    float dz = point.z - fixpoint.z;
    //right now, sqrt(dx^2 + dy^2) = distance(a,b).
    //we want to modify them so that sqrt(dx^2 + dy^2) = the given length.
    dx = dx * radius / distance(fixpoint,point);
    dy = dy * radius / distance(fixpoint,point);
    dz = dz * radius / distance(fixpoint, point);
    vec3 c;
    c.x = fixpoint.x + dx;
    c.y = fixpoint.y + dy;
    c.z = fixpoint.z + dz;
    return c;
}

/**
 * split one Triangle into 4 triangles - triforce style!
 */
std::vector<vec3> Sphere::splitTriangle(std::vector<vec3> &threePoints, unsigned int iterations) {

    std::vector<vec3> resultTriangle = threePoints;
    if (iterations > 0) {
        if (threePoints.size() != 3) {
            assert(false);
        }
        iterations--;

        //      B
        //     / \
        //    /   \
        //   D ___ E
        //  / \   / \
        // /   \ /   \
        //A_____F_____C
        //
        std::vector<vec3> triangleAFD;
        std::vector<vec3> triangleDFE;
        std::vector<vec3> triangleEFC;
        std::vector<vec3> triangleBDE;
        glm::vec3 a = threePoints[0];
        glm::vec3 b = threePoints[2];
        glm::vec3 c = threePoints[1];
        glm::vec3 d = a + (b - a) / 2.0f;
        glm::vec3 e = c + (b - c) / 2.0f;
        glm::vec3 f = a + (c - a) / 2.0f;

        triangleAFD.push_back(a);
        triangleAFD.push_back(f);
        triangleAFD.push_back(d);

        triangleEFC.push_back(f);
        triangleEFC.push_back(c);
        triangleEFC.push_back(e);

        triangleDFE.push_back(e);
        triangleDFE.push_back(d);
        triangleDFE.push_back(f);

        triangleBDE.push_back(d);
        triangleBDE.push_back(e);
        triangleBDE.push_back(b);

        triangleAFD = splitTriangle(triangleAFD, iterations);
        triangleDFE = splitTriangle(triangleDFE, iterations);
        triangleEFC = splitTriangle(triangleEFC, iterations);
        triangleBDE = splitTriangle(triangleBDE, iterations);

        resultTriangle.insert(resultTriangle.end(), triangleAFD.begin(), triangleAFD.end());
        resultTriangle.insert(resultTriangle.end(), triangleEFC.begin(), triangleEFC.end());
        resultTriangle.insert(resultTriangle.end(), triangleDFE.begin(), triangleDFE.end());
        resultTriangle.insert(resultTriangle.end(), triangleBDE.begin(), triangleBDE.end());
    }
    return  resultTriangle;
}

std::vector<vec4> Sphere::createColorVertices() {
    std::vector<vec4> colorVector;
    for(int i = 0; i < 8*pow(4.0f, ((float)detailIterations+1.0f)); i++) {
        colorVector.push_back(glm::vec4(0.0f,1.0f,0.0f,1.0f));
    }
    return colorVector;
}

Sphere::Sphere(float radius, GLint detailIterations): Sphere(radius) {
    this->detailIterations = detailIterations;
}

std::vector<vec4> Sphere::createColorVertices(glm::vec4 color) {
    std::vector<vec4> colorVector;
    for(int i = 0; i < 8*pow(4.0f, ((float)detailIterations+1.0f)); i++) {
        colorVector.push_back(color);
    }

    return colorVector;
}






















