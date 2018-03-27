#shader vertex
#version 330 core



layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texCoords;

//struct Object {
//	string tag = "Ball";
//
//};

struct Material {
	vec3 AmbientColour;
	vec3 DiffuseColour;
	vec3 SpecularColour;
	float Dissolve;
	int illum;
};

uniform Material u_Material;
uniform vec3 AmbientColour;
uniform mat4 u_ProjectionMat;
uniform mat4 u_ModelViewMat;

out Material v_Material

void main()
{
	gl_Position = vec4(position, 1.0) * u_ProjectioMat * u_ModelViewMat;
	v_Material = u_Material;
}										

#shader fragment
#version 330 core

in Material v_Material;
out vec4 colour;

void main()
{
	colour = vec4(v_Material.DiffuseColour, 1.0);
}