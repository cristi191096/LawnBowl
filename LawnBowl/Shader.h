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
#include <fstream>

class Shader
{
public:
	void ReadShader(const std::string& filePath);
	unsigned int CompileShader(unsigned int type, const std::string source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string fragmentShader);
	Shader();
	~Shader();
};

