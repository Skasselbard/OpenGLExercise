#version 130 

//input variable -- color information (interpolated)
in vec4 fsColor;

//create output variable -- this variable contains the color of the fragment
out vec4 fsColorBuffer;

void main() {  

  //set fragment color to black
  fsColorBuffer = fsColor;

}
