//
// Created by tom on 14.07.16.
//

#ifndef AUFGABE_SPHERE_H
#define AUFGABE_SPHERE_H


#include "Drawable.h"
//http://stackoverflow.com/a/5989676
class Sphere: public Drawable {
public:
    Sphere(float radius, unsigned int rings, unsigned int sectors);
    void draw();

protected:
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texcoords;
    std::vector<GLushort> indices;
};


#endif //AUFGABE_SPHERE_H
