#pragma once
#include <string>
#include "glm.hpp"
#include "Shader.h"


class Material
{

public:
	static Shader* shader;
	std::string name;
	glm::vec3 ambientColour;
	glm::vec3 diffuseColour;
	glm::vec3 specularColour;
	float dissolve; //Transparency
	int illum;		//Illumination
	std::string ambientTexName;
	std::string diffuseTexName;
	std::string bumpMapName;
	Material();
	~Material();

	void BindUniforms();
};

