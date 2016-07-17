//
// Created by tom on 16.07.16.
//

#ifndef AUFGABE_PYRAMID_H
#define AUFGABE_PYRAMID_H


#include "Drawable.h"

class Pyramid: public Drawable {
public:
    Pyramid();
private:
    std::vector<vec3> createPositionVertices();
    std::vector<vec4> createColorVertices();
    std::vector<vec4> createColorVertices(vec4 color);
};


#endif //AUFGABE_PYRAMID_H
