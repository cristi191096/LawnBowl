#pragma once

#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

enum class DrawType {
	ELEMENTS, ARRAYS
};

class Renderer
{
public:
	Renderer();
	~Renderer();
	//TODO here
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, DrawType type) const;
};

