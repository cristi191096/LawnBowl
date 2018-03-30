#include "Material.h"
#include "VertexBufferLayout.h"
#include "GameEngine.h"


void Material::SetDiffuseTexture(std::string diffuseTexName)
{
	diffTexName = diffuseTexName;
	diffuseTexture = new Texture(diffuseTexName);
}

//void Material::PushMaterial(VertexBufferLayout* ly) const
//{
//	ly->Push<float>(3);	//Ambient Colour
//	ly->Push<float>(3);	//Diffuse Colour
//	ly->Push<float>(3); //Specular Colour
//	ly->Push<float>(1); //Dissolve/Transparency
//	ly->Push<int>(1);	//Illumination
//}

Material::Material(std::string shaderPath)
{
	shader = new Shader(shaderPath);
	shader->Bind();
}

Material::Material(glm::vec4 colour, std::string shaderPath)
{
	if (shaderPath != GameEngine::currentShader->fileName) {
	shader = new Shader(shaderPath);
	GameEngine::currentShader = shader;
	shader->Bind();
	}
	else
	{
		shader = GameEngine::currentShader;
		shader->Bind();
	}
	
	ambientColour = glm::vec3(colour.r, colour.g, colour.b);
	diffuseColour = glm::vec3(colour.r, colour.g, colour.b);
	specularColour = glm::vec3(0, 0, 0);
	dissolve = colour.a;
}


Material::~Material()
{
	delete diffuseTexture;
	delete shader;
}

void Material::BindUniforms()
{
	//Set the uniforms within the shader and the program
	
	shader->SetUniformVec3("u_Material.ambientColour", ambientColour);
	shader->SetUniformVec3("u_Material.DiffuseColour", diffuseColour);
	shader->SetUniformVec3("u_Material.SpecularColour", specularColour);
	shader->SetUniform1f("u_Material.Dissolve", dissolve);
//	shader->SetUniform1i("u_Material.illum", illum);
}
