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


private:
    void addColorVertices();
    std::vector<glm::vec4> colorSubVertices(std::vector<glm::vec4> triangle, int iterations);
    void colorize();
    void createGeometry();
};


#endif //AUFGABE_SKY_H
