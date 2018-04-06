#pragma once
#include <string>
#include <vector>
#include "glm.hpp"
#include "Shader.h"
#include "Texture.h"

class VertexBufferLayout;

class Material
{

	void SetShader(const char* vshaderPath, const char* fshaderPath);
public:
	Shader* shader;
	std::vector<Texture> textures;
	std::string name;
	glm::vec3 ambientColour;
	glm::vec3 diffuseColour;
	glm::vec3 specularColour;
	float dissolve; //Transparency
	int illum;		//Illumination
	std::string ambientTexName;
	std::string diffTexName;
	std::string bumpMapName;
	//Texture* diffuseTexture;
	void SetDiffuseTexture(std::string diffuseTexName);
	//void PushMaterial(VertexBufferLayout* ly) const;
	Material(const char* vshaderPath = "Resources/Shaders/GameVertexShader.vs", const char* fShaderPath = "Resources/Shaders/GameFragmentShader.fs");
	Material(std::vector<Texture> tex, const char* vshaderPath = "Resources/Shaders/GameVertexShader.vs", const char* fShaderPath = "Resources/Shaders/GameFragmentShader.fs");
	Material(glm::vec4 colour, const char* vshaderPath = "Resources/Shaders/GameVertexShader.vs", const char* fShaderPath = "Resources/Shaders/GameFragmentShader.fs");
	~Material();

	void BindUniforms();
};

