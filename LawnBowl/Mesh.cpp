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
}

Mesh::~Mesh()
{
	delete buffer;
	delete indexBuffer;
	delete layout;
}

void Mesh::CreateSphere(int radius, int stacks, int slices)
{
	int count;
	delete buffer;
	delete indexBuffer;
	delete layout;
	count = 0;
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

			vertices.push_back(vert);

			count++;
		}
	}

	count = 0;
	// Calc The Index Positions
	for (int i = 0; i < slices * stacks + slices; ++i) {

		indices.push_back(i);
		count++;
		indices.push_back(i + slices + 1);
		count++;
		indices.push_back( i + slices);
		count++;

		indices.push_back( i + slices + 1);
		count++;
		indices.push_back(i);
		count++;
		indices.push_back(i + 1);
		count++;
	}

	count = 0;

	buffer = new VertexBuffer(vertices, vertices.size() * sizeof(Vertex));
	indexBuffer = new IndexBuffer(indices, indices.size());
	layout = new VertexBufferLayout();
	layout->Push<float>(3);
	layout->Push<float>(3);
	layout->Push<float>(2);
}
