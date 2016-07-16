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
    virtual std::string className(){return std::string("Sphere");};

protected:
    float radius;
    int detailIterations = 5;
    virtual std::vector<vec3> createPositionVertices();
    virtual std::vector<vec4> crerateColorVertices();
    virtual std::vector<vec4> crerateColorVertices(vec4 color);

private:
    std::vector<vec3> splitTriangle(std::vector<vec3> &threePoints, unsigned int iterations);
    vec3 normalize(vec3 fixpoint, vec3 point, float radius);
};

#endif //AUFGABE_SPHERE_H
