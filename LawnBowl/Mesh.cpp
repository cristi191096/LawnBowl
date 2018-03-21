#include "Mesh.h"




Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<Vertex>& verts, std::vector<unsigned int>& inds) :
	vertices(verts), indices(inds)
{
	buffer = VertexBuffer(vertices, sizeof(vertices));
}

Mesh::~Mesh()
{
}
