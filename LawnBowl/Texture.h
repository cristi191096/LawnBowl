#pragma once

#include <GL\glew.h>
#include <string>

class Texture
{
	unsigned int id;
	std::string filePath;
	unsigned char* localBuffer;
	int width, height, BPP;


public:
	//sampler2D for the shader. 
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
};

