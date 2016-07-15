#pragma once

#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Drawable.h"

/************************************************************************/
/* methods                                                              */
/************************************************************************/
void parseCommandLine(int argc, char **argv);

//camera
static bool sWireframe = false;
static double sLastUpdate = 0; //calculate time between each frame

/************************************************************************/
/* glut callbacks                                                       */
/************************************************************************/
//release all allocated resources
static void FinalizeApplication(void)
{
    //normally, shader and shader files have to be deleted
    //however, to simplify this program, we leave releasing resources to the operating system
}

// render loop
static void Display();

// size of window changed
static void Reshape(int w, int h);

void addDrawable(Drawable* drawable);

void draw();