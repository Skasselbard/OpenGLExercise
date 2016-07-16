//
// Created by tom on 15.07.16.
//

#ifndef AUFGABE_SKY_H
#define AUFGABE_SKY_H


#include "Sphere.h"

class Sky: public Sphere {
public:
    Sky();
    virtual std::string className(){return std::string("Sphere");}
    void calculateViewMatrix(glm::vec3 looktat, glm::vec3 eye);
    void draw();

private:
    virtual std::vector<vec4> crerateColorVertices();
    std::vector<glm::vec4> colorSubVertices(std::vector<glm::vec4> triangle, int iterations);
};


#endif //AUFGABE_SKY_H
