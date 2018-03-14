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

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>


struct ShaderSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
	ShaderSource source;
	unsigned int id;

	ShaderSource ReadShader(const std::string& filePath);
	unsigned int CompileShader(unsigned int type, const std::string source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string fragmentShader);

public:
	unsigned int GetProgramID();
	void Use();
	Shader(std::string& file);
	~Shader();
};

