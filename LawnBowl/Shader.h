#pragma once

#include "Renderer.h"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>


struct ShaderSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
	ShaderSource source;
	unsigned int id;
	std::unordered_map<std::string, int> uniformLocationCache;

	ShaderSource ReadShader(const std::string& filePath);
	unsigned int CompileShader(unsigned int type, const std::string source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string fragmentShader);
	unsigned int GetUniformLocation(const std::string& name);

public:
	unsigned int GetProgramID();
	Shader(std::string& file);
	~Shader();
	void Bind() const;
	void Unbind() const;

	//Set Uniforms
	//TODO: set the right uniforms maybe in more general way 
	//Eg. void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
};

