#pragma once

#include "Renderer.h"

class VertexBuffer
{

	unsigned int bufferID;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind();
	void Unbind();
};

