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
    Sphere(float radius, GLint detailIterations);
protected:
    float radius;
    int detailIterations = 5;
    virtual std::vector<vec3> createPositionVertices();
    virtual std::vector<vec4> createColorVertices();
    virtual std::vector<vec4> createColorVertices(vec4 color);

private:
    std::vector<vec3> splitTriangle(std::vector<vec3> &threePoints, unsigned int iterations);
    vec3 normalize(vec3 fixpoint, vec3 point, float radius);

    std::vector<vec3> createNormalVertices();
};

#endif //AUFGABE_SPHERE_H
