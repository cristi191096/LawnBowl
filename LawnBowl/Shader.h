#pragma once


#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>

#pragma comment(lib, "glew32d.lib") 
#endif

#include <glm.hpp>
#include <gtc\type_ptr.hpp>
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
	int GetUniformLocation(const std::string& name);

public:
	unsigned int GetProgramID();
	Shader(const std::string& file);
	~Shader();
	void Bind() const;
	void Unbind() const;

	//Set Uniforms
	//TODO: set the right uniforms maybe in more general way 
	//Eg. void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	//		template <typename T>
	//Eg2. void SetUniform<T>(const std::string& name, T param);

	void SetUniformVec2(const std::string& name, glm::vec2);
	void SetUniformVec3(const std::string& name, glm::vec3);
	void SetUniformVec4(const std::string& name, glm::vec4);
	void SetUniformMat4(const std::string& name, glm::mat4);
};

