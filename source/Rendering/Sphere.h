//
// Created by tom on 14.07.16.
//

#ifndef AUFGABE_SPHERE_H
#define AUFGABE_SPHERE_H


#include "Drawable.h"
//http://stackoverflow.com/a/7687312
class Sphere: public Drawable {
public:
    Sphere(float radius);
    void draw();

protected:
    std::vector<GLfloat> vertices;

private:
    float radius;
    //create an empty list of vertices
    std::vector<vec3> vertexArray;
    void createGeometry();
    void addVertices(std::vector<vec3> &vertexArray);
    std::vector<vec3> splitTriangle(std::vector<vec3> &threePoints, unsigned int iterations);
    vec3 normalize(vec3 fixpoint, vec3 point, float radius);
};


#endif //AUFGABE_SPHERE_H
