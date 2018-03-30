#include "Mesh.h"




Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<Vertex>& verts, std::vector<unsigned int>& inds) :
	vertices(verts), indices(inds)
{
	buffer = new VertexBuffer(vertices, vertices.size() * sizeof(Vertex));
	indexBuffer = new IndexBuffer(indices, indices.size());
	layout = new VertexBufferLayout();
	layout->Push<float>(3);
	layout->Push<float>(3);
	layout->Push<float>(2);
	buffer->Bind();
	indexBuffer->Bind();
}

void Mesh::SetMaterial(glm::vec4 colour)
{
	meshMaterial = new Material(colour);
	meshMaterial->BindUniforms();
}

Mesh::~Mesh()
{
	delete buffer;
	delete indexBuffer;
	delete layout;
	delete meshMaterial;
}

void Mesh::CreateSphere(int radius, int stacks, int slices)
{
	
	delete buffer;
	delete indexBuffer;
	delete layout;
	
	for (int i = 0; i <= stacks; ++i) {

		GLfloat V = i / (float)stacks;
		GLfloat phi = V * glm::pi<float>();

		// Loop Through Slices
		for (int j = 0; j <= slices; ++j) {

			GLfloat U = j / (float)slices;
			GLfloat theta = U * (glm::pi<float>() * 2);

			// Calc The Vertex Positions
			GLfloat x = cosf(theta) * sinf(phi);
			GLfloat y = cosf(phi);
			GLfloat z = sinf(theta) * sinf(phi);

			Vertex vert;

			vert.position = glm::vec3(x * radius, y * radius + 6.0, z * radius);
			vert.normal = glm::vec3(x, y, z); ///Sphere normals
			vert.uv = glm::vec2(0.0, 0.0);
			vertices.push_back(vert);


		}
	}


	// Calc The Index Positions
	for (int i = 0; i < slices * stacks + slices; ++i) {

		indices.push_back(i);

		indices.push_back(i + slices + 1);

		indices.push_back( i + slices);


		indices.push_back( i + slices + 1);

		indices.push_back(i);

		indices.push_back(i + 1);

	}

	

	buffer = new VertexBuffer(vertices, vertices.size() * sizeof(Vertex));
	indexBuffer = new IndexBuffer(indices, indices.size());
	layout = new VertexBufferLayout();
	layout->Push<float>(3);
	layout->Push<float>(3);
	layout->Push<float>(2);
	buffer->Bind();
	indexBuffer->Bind();
	//meshMaterial->PushMaterial(layout);
	
}
