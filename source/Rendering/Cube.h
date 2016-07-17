//
// Created by tom on 13.07.16.
//

#ifndef AUFGABE_MOVEMENT_H
#define AUFGABE_MOVEMENT_H

#include "Drawable.h"

class Cube: public Drawable{
public:
    Cube();
private:
    std::vector<vec3> createPositionVertices();
    std::vector<vec4> createColorVertices();
    std::vector<vec4> createColorVertices(vec4 color);
    //std::vector<vec3> createNormalVertices();
};

#endif //AUFGABE_MOVEMENT_H
