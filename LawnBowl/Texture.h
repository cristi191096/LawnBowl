#pragma once

#include <GL\glew.h>
#include <string>



class Texture
{
	unsigned int id;
	unsigned char* localBuffer;
	int width, height, BPP;

public:
	std::string filePath;
	std::string type; // like the name in the shader (eg. "texture_diffuse", "texture_specular")
	//sampler2D for the shader. 
	Texture(const std::string& path, GLenum glTarget = GL_TEXTURE_2D);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
};

