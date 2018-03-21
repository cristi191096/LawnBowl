#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Material.h"
#include "glm.hpp"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};

class Mesh
{
	VertexBuffer* buffer;
	IndexBuffer* indexBuffer;

public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::string name;

	Material meshMaterial;
	Mesh();
	Mesh(std::vector<Vertex>& verts, std::vector<unsigned int>& inds);
	~Mesh();
};

