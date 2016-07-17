//
// Created by tom on 15.07.16.
//

#ifndef AUFGABE_SKY_H
#define AUFGABE_SKY_H


#include "Sphere.h"

class Sky: public Sphere {
public:
    Sky();
    void calculateViewMatrix(glm::vec3 looktat, glm::vec3 eye);
    void draw();

private:
    std::vector<vec4> createColorVertices();
    std::vector<glm::vec4> colorSubVertices(std::vector<glm::vec4> triangle, int iterations);

    std::vector<vec3> createNormalVertices();
};


#endif //AUFGABE_SKY_H
