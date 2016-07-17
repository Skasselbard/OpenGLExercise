//
// Created by tom on 16.07.16.
//

#include "Pyramid.h"

Pyramid::Pyramid() : Drawable() {

}

std::vector<vec3> Pyramid::createPositionVertices() {
    const vec3 frontLeftBottom    = vec3(-0.5, 0.0, 0.5);//0
    const vec3 frontRightBottom   = vec3(0.5, 0.0, 0.5);//1
    const vec3 Top                = vec3(0.0, 1.0, 0.0);//2
    const vec3 backLeftBottom     = vec3(-0.5, 0.0, -0.5);//4
    const vec3 backRightBottom    = vec3(0.5, 0.0, -0.5);//5

    std::vector<vec3> vertexArray;

    //Bottom
    vertexArray.push_back(frontLeftBottom);
    vertexArray.push_back(backLeftBottom);
    vertexArray.push_back(frontRightBottom);

    vertexArray.push_back(backLeftBottom);
    vertexArray.push_back(backRightBottom);
    vertexArray.push_back(frontRightBottom);
    //end Bottom

    //Front
    vertexArray.push_back(frontLeftBottom);
    vertexArray.push_back(frontRightBottom);
    vertexArray.push_back(Top);
    //end Front

    //Back
    vertexArray.push_back(backRightBottom);
    vertexArray.push_back(backLeftBottom);
    vertexArray.push_back(Top);
    //end Back

    //Left
    vertexArray.push_back(backLeftBottom);
    vertexArray.push_back(frontLeftBottom);
    vertexArray.push_back(Top);
    //end Left

    //Right
    vertexArray.push_back(frontRightBottom);
    vertexArray.push_back(backRightBottom);
    vertexArray.push_back(Top);
    //end Right

    return vertexArray;}

std::vector<vec4> Pyramid::createColorVertices() {
    std::vector<vec4> colorArray;
    for(int i = 0; i<6;i++){
        colorArray.push_back(vec4(0,1,1,1));
    }
    for (int i=0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 0)
                colorArray.push_back(vec4(1, 0, 0, 1));
            if (i == 2)
                colorArray.push_back(vec4(0, 1, 0, 1));
            if (i == 1)
                colorArray.push_back(vec4(0, 0, 1, 1));
            if (i == 3)
                colorArray.push_back(vec4(1,1,0,1));
        }
    }
    return colorArray;
}

std::vector<vec4> Pyramid::createColorVertices(vec4 color) {
    std::vector<vec4> colorArray;
    for(int i = 0; i<18;i++){
        colorArray.push_back(color);
    }
    return colorArray;
}








