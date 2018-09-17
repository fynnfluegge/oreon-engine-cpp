#pragma once
#include <vector>
#include "vertex.h"

class Mesh {
public:
	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<uint64_t> indices);
	std::vector<Vertex> getVertices() const;
	std::vector<uint64_t> getIndices() const;
private:
	std::vector<Vertex> vertices;
	std::vector<uint64_t> indices;
	uint64_t instances;
	VertexLayout vertexLayout;
	bool tangentSpace;
	bool instanced;
};
