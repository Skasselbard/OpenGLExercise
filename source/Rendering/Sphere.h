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
    float radius;
    std::vector<vec3> vertexArray;
    const int detailIterations = 2;
    std::vector<vec4> colorArray;
    virtual void createGeometry();
    void addVertices(std::vector<vec3> &vertexArray);

private:
    std::vector<vec3> splitTriangle(std::vector<vec3> &threePoints, unsigned int iterations);
    vec3 normalize(vec3 fixpoint, vec3 point, float radius);
};

#endif //AUFGABE_SPHERE_H
