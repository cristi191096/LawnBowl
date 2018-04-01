#pragma once


class VertexArray;
class IndexBuffer;

enum class DrawType {
	ELEMENTS, ARRAYS
};

class Renderer
{
public:
	Renderer();
	~Renderer();
	//TODO here
	static void Draw(VertexArray* va, IndexBuffer* ib, int vertsNum, DrawType type);
	static void Clear();
};

