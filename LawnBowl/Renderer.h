#pragma once

#include "Shader.h"
#include "VertexArray.h"

class Renderer
{
public:
	Renderer();
	~Renderer();
	//TODO here
	void Draw(const VertexArray& va, const Shader& shader) const;
};

