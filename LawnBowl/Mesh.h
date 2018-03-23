#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Material.h"
#include "glm.hpp"
#include "gtc\constants.hpp"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};

class Mesh
{

public:
	VertexBufferLayout* layout;
	VertexBuffer* buffer;
	IndexBuffer* indexBuffer;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices = { 0 };
	std::string name;

	Material meshMaterial;
	Mesh();
	Mesh(std::vector<Vertex>& verts, std::vector<unsigned int>& inds);
	~Mesh();

	void CreateSphere(int radius, int stacks, int slices);
};

