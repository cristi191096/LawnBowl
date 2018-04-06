#include "Mesh.h"
#include "Renderer.h"


void Mesh::SetMaterial(glm::vec4 colour)
{
	meshMaterial = new Material(colour);
	meshMaterial->BindUniforms();
}

Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<Vertex> verts, std::vector<unsigned int> inds) :
	vertices(verts), indices(inds)
{
	meshMaterial = new Material();
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

Mesh::Mesh(std::vector<Vertex> verts, std::vector<unsigned int> inds, std::vector<Texture> tex)
{
	meshMaterial = new Material(tex);
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


void Mesh::Draw() const
{
	// bind appropriate textures
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

	for (unsigned int i = 0; i < this->meshMaterial->textures.size(); i++) {

		glActiveTexture(GL_TEXTURE0 + i);
		std::string number;
		std::string name = this->meshMaterial->textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++); // transfer unsigned int to stream
		else if (name == "texture_normal")
			number = std::to_string(normalNr++); // transfer unsigned int to stream
		else if (name == "texture_height")
			number = std::to_string(heightNr++); // transfer unsigned int to stream

		meshMaterial->shader->SetUniform1i((name + number), i);
		meshMaterial->textures[i].Bind();
	}

	Renderer::Draw(VAO, indexBuffer, vertices.size(), DrawType::ELEMENTS);
	glActiveTexture(GL_TEXTURE0);
}

Mesh::~Mesh()
{
	//if (this != nullptr) {
	//	delete buffer;
	//	delete indexBuffer;
	//	delete layout;
	//	delete meshMaterial;
	//}
	//else
	//{
	//	buffer = nullptr;
	//	indexBuffer = nullptr;
	//	layout = nullptr;
	//	meshMaterial = nullptr;
	//}
}

