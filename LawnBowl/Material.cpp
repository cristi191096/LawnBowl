#include "Material.h"


Shader* Material::shader = new Shader("GameShaders.shader");

Material::Material()
{
	shader->Bind();
}


Material::~Material()
{
	
}

void Material::BindUniforms()
{
	//Set the uniforms within the shader.
}
