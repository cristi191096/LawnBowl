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
	glm::vec3 tangent;
	glm::vec3 biTangent;
};

class Mesh
{
	

public:
	Material* meshMaterial;
	VertexBufferLayout* layout;
	VertexBuffer* buffer;
	IndexBuffer* indexBuffer;
	VertexArray* VAO;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices/* = { 0 }*/;
	std::string name;

	Mesh();
	Mesh(std::vector<Vertex> verts, std::vector<unsigned int> inds);
	Mesh(std::vector<Vertex> verts, std::vector<unsigned int> inds, std::vector<Texture> tex);
	void SetMaterial(glm::vec4 colour = glm::vec4(1,0,1,1));
	void Draw() const;
	~Mesh();

};

