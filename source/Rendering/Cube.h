//
// Created by tom on 13.07.16.
//

#ifndef AUFGABE_MOVEMENT_H
#define AUFGABE_MOVEMENT_H

#include "Drawable.h"

class Cube: public Drawable{
public:
    Cube(std::string const &vertexShaderFilePath, std::string const &fragmentShaderFilePath);
    Cube();
    void draw();
    void scale(float x, float y, float z);
    void translate(float x, float y, float z);
private:
    void createGeometry(void);
    void addCubeVertices(std::vector<vec3> &vertexArray);
    void colorise(std::vector<vec4> &colorArray);
};

#endif //AUFGABE_MOVEMENT_H
