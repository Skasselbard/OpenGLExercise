//
// Created by tom on 13.07.16.
//
#include "Cube.h"

void Cube::createGeometry(void) {
    //create an empty list of vertices
    std::vector<vec3> vertexArray;

    addCubeVertices(vertexArray);

    //vertex array object -- wraps up geometry and consists of multiple vertex buffer objects and their stats
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    //create vertex buffer object -- a list of vertices, normals etc. In this case wraps up list of vertices. It exists on GPU side and allows transferring geometry data from CPU to GPU
    GLuint vboVertex;
    glGenBuffers(1, &vboVertex);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertex);

    //transfer vertices
    //void glBufferData(GLenum  target, GLsizeiptr  size, const GLvoid *  data, GLenum  usage);
    glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(vec3), vertexArray.data(), GL_STATIC_DRAW);

    //get attribute index for variable vsPosition
    GLint attributeIndex = glGetAttribLocation(shaderProgramID, "vsPosition");

    //tell GPU how to interpret this data for the specified attribute
    glVertexAttribPointer(attributeIndex, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    //activate this attribute
    glEnableVertexAttribArray(attributeIndex);

    //unbind vbo -- saves all stats given to this objects until this point
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //create empty list of color attributes
    std::vector<vec4> color;
    colorise(color);

    //create another vertex buffer object -- a list of color attributes for each vertex. Must have the same number of elements, as the vertex list
    GLuint vboColor;
    glGenBuffers(1, &vboColor);
    glBindBuffer(GL_ARRAY_BUFFER, vboColor);

    //transfer color attributes
    glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(vec4), color.data(), GL_STATIC_DRAW);

    //get attribute index for variable vsPosition
    attributeIndex = glGetAttribLocation(shaderProgramID, "vsColor");

    //tell GPU how to interpret this data for the specified attribute
    glVertexAttribPointer(attributeIndex, 4, GL_FLOAT, GL_FALSE, 0, NULL);

    //activate this attribute
    glEnableVertexAttribArray(attributeIndex);


    //unbind vertex array objects -- saves all stats given to this objects until this point
    glBindVertexArray(0);

}

void Cube::addCubeVertices(std::vector<vec3> &vertexArray) {
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
}

void Cube::colorise(std::vector<vec4> &colorArray) {
    for (float i=0; i < 6; i++){
        for (int j = 0; j<6; j++) {
            if (i == 0)
                colorArray.push_back(vec4(1,0,0,1));
            if (i == 1)
                colorArray.push_back(vec4(0,1,0,1));
            if (i == 2)
                colorArray.push_back(vec4(0,0,1,1));
            if (i == 3)
                colorArray.push_back(vec4(1,1,0,1));
            if (i == 4)
                colorArray.push_back(vec4(1,0,1,1));
            if (i == 5)
                colorArray.push_back(vec4(0,1,1,1));
        }
    }
}

Cube::Cube(std::string const &vertexShaderFilePath, std::string const &fragmentShaderFilePath) {
    setFragmentShaderFile(vertexShaderFilePath);
    setVertexShaderFile(fragmentShaderFilePath);
    initShader();
}

void Cube::draw() {
    //createGeometry();
    glUseProgram(shaderProgramID);

    GLint uniformLocation(0);
    uniformLocation = glGetUniformLocation(shaderProgramID, "modelMatrix");
    glUniformMatrix4fv(uniformLocation, 1, false, &modelMatrix[0][0]);

    glBindVertexArray(vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glUseProgram(0);
}

Cube::Cube() {

}



















