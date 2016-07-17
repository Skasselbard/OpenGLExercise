#version 130

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


in  vec4 fsColor;
in	vec3 Position;
in	vec3 Normal;

out vec4 FragColor;

LightInfo Light[LIGHTCOUNT];
MaterialInfo Material;

void light( int lightIndex, vec3 position, vec3 norm, out vec3 ambient, out vec3 diffuse, out vec3 spec )
{
	vec3 n = normalize( norm );
	vec3 s = normalize( Light[lightIndex].Position - position );
	vec3 v = normalize( -position );
	vec3 r = reflect( -s, n );

	ambient = Light[lightIndex].Ambient * Material.Ambient;

	float sDotN = max( dot( s, n ), 0.0 );
	diffuse = Light[lightIndex].Diffuse * Material.Diffuse * sDotN;


	spec = Light[lightIndex].Specular * Material.Specular * pow( max( dot(r,v) , 0.0 ), Material.Shininess );
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
    Material.Ambient = vec3(0.3,0.3,0.3);
    Material.Shininess = 1.0f;

	vec3 ambientSum = vec3(0);
	vec3 diffuseSum = vec3(0);
	vec3 specSum = vec3(0);
	vec3 ambient, diffuse, spec;

	if ( gl_FrontFacing )
	{
		for( int i=0; i<LIGHTCOUNT; ++i )
		{
			light( i, Position, Normal, ambient, diffuse, spec );
			ambientSum += ambient;
			diffuseSum += diffuse;
			specSum += spec;
		}
	}
	else
	{
		for( int i=0; i<LIGHTCOUNT; ++i )
		{
			light( i, Position, -Normal, ambient, diffuse, spec );
			ambientSum += ambient;
			diffuseSum += diffuse;
			specSum += spec;
		}
	}
	ambientSum /= LIGHTCOUNT;

	FragColor = (vec4( ambientSum + diffuseSum, 1 ) + vec4( specSum, 1 ))+fsColor;
}