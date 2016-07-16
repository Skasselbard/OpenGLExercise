//
// Created by tom on 16.07.16.
//

#ifndef AUFGABE_PYRAMID_H
#define AUFGABE_PYRAMID_H


#include "Drawable.h"

class Pyramid: public Drawable {
public:
    Pyramid();
    void draw();
    virtual std::string className(){return std::string("Pyramid");}
private:
    void createGeometry(void);
    void addCubeVertices(std::vector<vec3> &vertexArray);
    void colorise(std::vector<vec4> &colorArray);
};


#endif //AUFGABE_PYRAMID_H
