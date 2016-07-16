//
// Created by tom on 13.07.16.
//
#include "Cube.h"

std::vector<vec3> Cube::createPositionVertices() {
    //http://stackoverflow.com/a/8142461
    //    6---7
    //   /|  /|
    //  2---3 |
    //  | 4-|-5
    //  |/  |/
    //  0---1
    const vec3 frontLeftBottom    = vec3(0.0, 0.0, -0.0);//0
    const vec3 frontRightBottom   = vec3(1.0, 0.0, -0.0);//1
    const vec3 frontLeftTop       = vec3(0.0, 1.0, -0.0);//2
    const vec3 frontRightTop      = vec3(1.0, 1.0, -0.0);//3
    const vec3 backLeftBottom     = vec3(0.0, 0.0, -1.0);//4
    const vec3 backRightBottom    = vec3(1.0, 0.0, -1.0);//5
    const vec3 backLeftTop        = vec3(0.0, 1.0, -1.0);//6
    const vec3 backRightTop       = vec3(1.0, 1.0, -1.0);//7

    std::vector<vec3> vertexArray;

    //Top
    //627
    vertexArray.push_back(backLeftTop);
    vertexArray.push_back(frontLeftTop);
    vertexArray.push_back(backRightTop);
    //237
    vertexArray.push_back(frontLeftTop);
    vertexArray.push_back(frontRightTop);
    vertexArray.push_back(backRightTop);
    //end Top

    //Bottom
    //041
    vertexArray.push_back(frontLeftBottom);
    vertexArray.push_back(backLeftBottom);
    vertexArray.push_back(frontRightBottom);
    //451
    vertexArray.push_back(backLeftBottom);
    vertexArray.push_back(backRightBottom);
    vertexArray.push_back(frontRightBottom);
    //end Bottom

    //Front
    //012
    vertexArray.push_back(frontLeftBottom);
    vertexArray.push_back(frontRightBottom);
    vertexArray.push_back(frontLeftTop);
    //132
    vertexArray.push_back(frontRightBottom);
    vertexArray.push_back(frontRightTop);
    vertexArray.push_back(frontLeftTop);
    //end Front

    //Back
    //756
    vertexArray.push_back(backRightTop);
    vertexArray.push_back(backRightBottom);
    vertexArray.push_back(backLeftTop);
    //546
    vertexArray.push_back(backRightBottom);
    vertexArray.push_back(backLeftBottom);
    vertexArray.push_back(backLeftTop);
    //end Back

    //Left
    //642
    vertexArray.push_back(backLeftTop);
    vertexArray.push_back(backLeftBottom);
    vertexArray.push_back(frontLeftTop);
    //402
    vertexArray.push_back(backLeftBottom);
    vertexArray.push_back(frontLeftBottom);
    vertexArray.push_back(frontLeftTop);
    //end Left

    //Right
    //317
    vertexArray.push_back(frontRightTop);
    vertexArray.push_back(frontRightBottom);
    vertexArray.push_back(backRightTop);
    //157
    vertexArray.push_back(frontRightBottom);
    vertexArray.push_back(backRightBottom);
    vertexArray.push_back(backRightTop);
    //end Right

    return vertexArray;
}

std::vector<vec4> Cube::crerateColorVertices() {
    std::vector<vec4> colorArray;
    for (float i=0; i < 6; i++){
        for (int j = 0; j<6; j++) {
            if (i == 0)
                colorArray.push_back(vec4(1,0,0,1));
            if (i == 2)
                colorArray.push_back(vec4(0,1,0,1));
            if (i == 1)
                colorArray.push_back(vec4(0,0,1,1));
            if (i == 3)
                colorArray.push_back(vec4(1,1,0,1));
            if (i == 4)
                colorArray.push_back(vec4(1,0,1,1));
            if (i == 5)
                colorArray.push_back(vec4(0,1,1,1));
        }
    }
    return colorArray;
}

Cube::Cube() : Drawable(){
}

std::vector<vec4> Cube::crerateColorVertices(vec4 color) {
    std::vector<vec4> colorArray;
    for (float i=0; i < 6; i++){
        for (int j = 0; j<6; j++) {
                colorArray.push_back(color);
        }
    }
    return colorArray;}





















