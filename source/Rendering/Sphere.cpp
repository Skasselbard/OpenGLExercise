//
// Created by tom on 14.07.16.
//

#include <glm/gtx/transform.hpp>
#include "Sphere.h"

Sphere::Sphere(float radius) {
    this->radius=radius;
}

void Sphere::draw() {

    glUseProgram(shaderProgramID);

    GLint uniformLocation(0);
    uniformLocation = glGetUniformLocation(shaderProgramID, "modelMatrix");
    glUniformMatrix4fv(uniformLocation, 1, false, &modelMatrix[0][0]);

    glBindVertexArray(vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, vertexArray.size());
    glBindVertexArray(0);

    glUseProgram(0);
}

void Sphere::createGeometry() {
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
    glBindVertexArray(0);
}

void Sphere::addVertices(std::vector<vec3> &vertexArray) {
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

    const int detailIterations = 5;

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
    vertexArrayBottomFront.push_back(frontRight);
    vertexArrayBottomFront.push_back(frontLeft);
    vertexArrayBottomFront.push_back(bottom);
    vertexArrayBottomFront= splitTriangle(vertexArrayBottomFront, detailIterations);
    //BottomLeft
    vertexArrayBottomLeft.push_back(frontLeft);
    vertexArrayBottomLeft.push_back(backLeft);
    vertexArrayBottomLeft.push_back(bottom);
    vertexArrayBottomLeft= splitTriangle(vertexArrayBottomLeft, detailIterations);
    //BottomRight
    vertexArrayBottomRight.push_back(backRight);
    vertexArrayBottomRight.push_back(frontRight);
    vertexArrayBottomRight.push_back(bottom);
    vertexArrayBottomRight= splitTriangle(vertexArrayBottomRight, detailIterations);
    //BottomBack
    vertexArrayBottomBack.push_back(backLeft);
    vertexArrayBottomBack.push_back(backRight);
    vertexArrayBottomBack.push_back(bottom);
    vertexArrayBottomBack= splitTriangle(vertexArrayBottomBack, detailIterations);


    vertexArray.insert(vertexArray.end(),vertexArrayTopFront.begin(), vertexArrayTopFront.end());
    vertexArray.insert(vertexArray.end(),vertexArrayTopLeft.begin(), vertexArrayTopLeft.end());
    vertexArray.insert(vertexArray.end(),vertexArrayTopRight.begin(), vertexArrayTopRight.end());
    vertexArray.insert(vertexArray.end(),vertexArrayTopBack.begin(), vertexArrayTopBack.end());
    vertexArray.insert(vertexArray.end(),vertexArrayBottomFront.begin(), vertexArrayBottomFront.end());
    vertexArray.insert(vertexArray.end(),vertexArrayBottomLeft.begin(), vertexArrayBottomLeft.end());
    vertexArray.insert(vertexArray.end(),vertexArrayBottomRight.begin(), vertexArrayBottomRight.end());
    vertexArray.insert(vertexArray.end(),vertexArrayBottomBack.begin(), vertexArrayBottomBack.end());


    for (int i = 0; i < vertexArray.size(); i++){
        vertexArray[i] = normalize(vertexArray[i],glm::vec3(0.0f,0.0f,0.0f),-radius*10);
    }
    scale(0.5f/5.0f);
}

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

std::vector<vec3> Sphere::splitTriangle(std::vector<vec3> &threePoints, unsigned int iterations) {
    if(threePoints.size() != 3){
        assert(false);
    }
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
    std::vector<vec3> resultTriangle;
    glm::vec3 a = threePoints[0];
    glm::vec3 b = threePoints[2];
    glm::vec3 c = threePoints[1];
    glm::vec3 d = a + (b-a)/2.0f;
    glm::vec3 e = c + (b-c)/2.0f;
    glm::vec3 f = a + (c-a)/2.0f;

    triangleAFD.push_back(a);
    triangleAFD.push_back(f);
    triangleAFD.push_back(d);

    triangleDFE.push_back(d);
    triangleDFE.push_back(f);
    triangleDFE.push_back(e);

    triangleEFC.push_back(c);
    triangleEFC.push_back(e);
    triangleEFC.push_back(f);

    triangleBDE.push_back(e);
    triangleBDE.push_back(b);
    triangleBDE.push_back(d);

    if (iterations > 0){
        iterations--;
        triangleAFD = splitTriangle(triangleAFD, iterations);
        triangleDFE = splitTriangle(triangleDFE, iterations);
        triangleEFC = splitTriangle(triangleEFC, iterations);
        triangleBDE = splitTriangle(triangleBDE, iterations);
    }
    resultTriangle.insert(resultTriangle.end(), triangleAFD.begin(), triangleAFD.end());
    resultTriangle.insert(resultTriangle.end(), triangleDFE.begin(), triangleDFE.end());
    resultTriangle.insert(resultTriangle.end(), triangleEFC.begin(), triangleEFC.end());
    resultTriangle.insert(resultTriangle.end(), triangleBDE.begin(), triangleBDE.end());
    return  resultTriangle;
}












