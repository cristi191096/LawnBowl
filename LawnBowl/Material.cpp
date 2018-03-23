#include "Material.h"


Shader* Material::shader;

Material::Material()
{
	
}


Material::~Material()
{
	
}

void Material::BindUniforms()
{
	//Set the uniforms within the shader and the program
	shader->SetUniformVec3("u_AmbientColour", ambientColour);
	shader->SetUniformVec3("u_DiffuseColour", diffuseColour);
	shader->SetUniformVec3("u_SpecularColour", specularColour);
	shader->SetUniform1f("u_Dissolve", dissolve);
}
