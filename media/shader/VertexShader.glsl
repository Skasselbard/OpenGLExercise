#version 130 

//input -- vertices
in vec3 vsPosition;
//in vec3 vsNormal;

//input -- color attributes
in vec4 vsColor;

//output variable to fragment shader -- color attribute per vertex
out vec4 fsColor;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main() {
  //set intern variable gl_Position to fragment position (in camera space, which is the same as the vertex coordinates in this case) -- coordinates must be homogenous
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vsPosition, 1.0);

  //transfer color information
  fsColor = vsColor;
}
