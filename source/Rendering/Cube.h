//
// Created by tom on 13.07.16.
//

#ifndef AUFGABE_MOVEMENT_H
#define AUFGABE_MOVEMENT_H

#include "Drawable.h"

class Cube: public Drawable{
public:
    Cube();
    void draw();
private:
    void createGeometry(void);
    void addCubeVertices(std::vector<vec3> &vertexArray);
    void colorise(std::vector<vec4> &colorArray);
};

#endif //AUFGABE_MOVEMENT_H
