#pragma once


struct Vertex;

class IndexBuffer
{

	unsigned int bufferID;
	unsigned int count;

public:
	IndexBuffer(const std::vector<unsigned int>& data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return this->count; }
};

