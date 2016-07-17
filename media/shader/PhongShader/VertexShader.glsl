#version 130
//https://www.opengl.org/discussion_boards/showthread.php/185829-Help-with-Gouraud-Phong-Shading-in-Shaders
in vec3 vsPosition;
in vec3 vsNormal;
in vec4 vsColor;

out vec3 Position;
out vec3 Normal;
out vec4 fsColor;

uniform mat3 normalMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main()
{
	Normal = normalize( normalMatrix * vsNormal );
	Position = vec3( viewMatrix * modelMatrix * vec4( vsPosition, 1 ) );
	fsColor = vsColor;

  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vsPosition, 1.0);

}