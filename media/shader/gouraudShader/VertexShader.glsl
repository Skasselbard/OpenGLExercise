#version 130
//https://www.opengl.org/discussion_boards/showthread.php/185829-Help-with-Gouraud-Phong-Shading-in-Shaders
in vec3 vsPosition;
in vec4 vsColor;
in vec3 vsNormal;

out vec4 FrontColor;
out	vec4 BackColor;

struct LightInfo{
	vec3 Position;	//Light Position in eye-coords
	vec3 Ambient;		//Ambient light intensity
	vec3 Diffuse;		//Diffuse light intensity
	vec3 Specular;		//Specular light intensity
};

struct MaterialInfo{
	vec3 Ambient;			//Ambient reflectivity
	vec3 Diffuse;			//Diffuse reflectivity
	vec3 Specular;			//Specular reflectivity
	float Shininess;	//Specular shininess factor
};
const int LIGHTCOUNT = 1;

 LightInfo Light[LIGHTCOUNT];
 MaterialInfo Material;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat3 normalMatrix;
uniform mat4 projectionMatrix;


void getEyeSpace( out vec3 norm, out vec3 position )
{
	norm = normalize( normalMatrix * vsNormal );
	position = vec3(viewMatrix * modelMatrix * vec4( vsPosition, 1 ) );
}

vec3 light( int lightIndex, vec3 position, vec3 norm )
{
	vec3 s = normalize( vec3( Light[lightIndex].Position - position ) );
	vec3 v = normalize( -position.xyz );
	vec3 r = reflect( -s, norm );

	vec3 ambient = Light[lightIndex].Ambient * Material.Ambient;

	float sDotN = max( dot( s, norm ), 0.0 );
	vec3 diffuse = Light[lightIndex].Diffuse * Material.Diffuse * sDotN;

	vec3 spec = vec3( 0.0 );
	if ( sDotN > 0.0 ){
		spec = Light[lightIndex].Specular * Material.Specular * pow( max( dot(r,v) , 0.0 ), Material.Shininess );
    }
	return ambient + diffuse + spec;
}

void main()
{
    LightInfo lightInfo;
    lightInfo.Ambient = vec3(0.5,0.5,0.5);
    lightInfo.Diffuse = vec3(0.9,0.5,0.3);
    lightInfo.Specular = vec3(0.5,0.5,0.5);
    lightInfo.Position = vec3(-10,40,10);
    Light[0] = lightInfo;
    Material.Specular = vec3(0.5,0.5,0.5);
    Material.Diffuse = vec3(0.5,0.5,0.5);
    Material.Ambient = vec3(0.5,0.5,0.5);
    Material.Shininess = 1.0f;

	vec3 eyeNorm;
	vec3 eyePosition;
	getEyeSpace( eyeNorm, eyePosition );

	FrontColor = vsColor;
	BackColor = vsColor;

	for( int i=0; i<LIGHTCOUNT; ++i )
	{
		FrontColor += vec4(light( i, eyePosition, eyeNorm ),1);
		BackColor +=  vec4(light( i, eyePosition, -eyeNorm ),1);
	}

	gl_Position = projectionMatrix * viewMatrix * modelMatrix* vec4( vsPosition, 1 );
}