#include "mesh.h"

Mesh::Mesh() : tangentSpace(false), instanced(false)
{
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint64_t> indices)
	: vertices(vertices), indices(indices)
{
}

std::vector<Vertex> Mesh::getVertices() const
{
	return vertices;
}

std::vector<uint64_t> Mesh::getIndices() const
{
	return indices;
}

