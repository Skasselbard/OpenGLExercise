//
// Created by tom on 13.07.16.
//

#ifndef AUFGABE_MOVEMENT_H
#define AUFGABE_MOVEMENT_H

#include "Drawable.h"

class Cube: public Drawable{
public:
    Cube();
    virtual std::string className(){return std::string("Cube");}
private:
    std::vector<vec3> createPositionVertices();
    std::vector<vec4> crerateColorVertices();
    std::vector<vec4> crerateColorVertices(vec4 color);
};

#endif //AUFGABE_MOVEMENT_H
