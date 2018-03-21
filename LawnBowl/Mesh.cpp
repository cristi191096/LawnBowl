#include "Mesh.h"




Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<Vertex>& verts, std::vector<unsigned int>& inds) :
	vertices(verts), indices(inds)
{
	buffer = new VertexBuffer(vertices, sizeof(vertices));
	//indexBuffer = new IndexBuffer(indices, )
}

Mesh::~Mesh()
{
	delete buffer;
	//delete indexBuffer;
}
