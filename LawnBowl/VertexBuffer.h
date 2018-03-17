#pragma once


class VertexBuffer
{

	unsigned int bufferID;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};

