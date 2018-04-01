#include "Mesh.h"
#include "Renderer.h"



Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<Vertex>& verts, std::vector<unsigned int>& inds) :
	vertices(verts), indices(inds)
{
	VAO = new VertexArray();
	buffer = new VertexBuffer(vertices, vertices.size() * sizeof(Vertex));
	indexBuffer = new IndexBuffer(indices, indices.size());
	layout = new VertexBufferLayout();
	layout->Push<float>(3);
	layout->Push<float>(3);
	layout->Push<float>(2);
	VAO->Bind();
	buffer->Bind();
	indexBuffer->Bind();
	VAO->AddBuffer(*buffer, *layout);
	VAO->Unbind();
}

void Mesh::SetMaterial(glm::vec4 colour)
{
	meshMaterial = new Material(colour);
	meshMaterial->BindUniforms();
}

void Mesh::Draw() const
{
	Renderer::Draw(VAO, indexBuffer, vertices.size(), DrawType::ELEMENTS);
}

Mesh::~Mesh()
{
	delete buffer;
	delete indexBuffer;
	delete layout;
	delete meshMaterial;
}

