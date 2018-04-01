#include "Texture.h"
#include "stb_image.h"
#include <iostream>


Texture::Texture(const std::string& path, GLenum glTarget)
	: id(0), filePath(path), localBuffer(nullptr), 
	width(0), height(0), BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	localBuffer = stbi_load(path.c_str(), &width, &height, &BPP, 4);

	glGenTextures(1, &id);
	if (localBuffer) {

		GLenum format;
		if (BPP == 1) format = GL_RED;
		else if (BPP == 3) format = GL_RGB;
		else if (BPP == 4) format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(glTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(glTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(glTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(glTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, localBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(localBuffer);
	}
	else
	{
		std::cout << "Texture at path: " << path << " failed to load!" << std::endl;
		stbi_image_free(localBuffer);
	}
}


Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
