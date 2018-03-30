#pragma once
#include <string>
#include "glm.hpp"
#include "Shader.h"
#include "Texture.h"

class VertexBufferLayout;

class Material
{

public:
	Shader* shader;
	std::string name;
	glm::vec3 ambientColour;
	glm::vec3 diffuseColour;
	glm::vec3 specularColour;
	float dissolve; //Transparency
	int illum;		//Illumination
	std::string ambientTexName;
	std::string diffTexName;
	std::string bumpMapName;
	Texture* diffuseTexture;
	void SetDiffuseTexture(std::string diffuseTexName);
	//void PushMaterial(VertexBufferLayout* ly) const;
	Material(std::string shaderPath = "Resources/Shaders/GameShaders.shader");
	Material(glm::vec4 colour, std::string shaderPath = "Resources/Shaders/GameShaders.shader");
	~Material();

	void BindUniforms();
};

