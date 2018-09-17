#include "vertex.h"

Vertex::Vertex()
{
}

Vertex::Vertex(Vec3f pos) : position(pos)
{
}

Vec3f Vertex::getPosition() const
{
	return position;
}

Vec3f Vertex::getNormal() const
{
	return normal;
}

Vec2f Vertex::getUv() const
{
	return uv;
}

Vec3f Vertex::getTangent() const
{
	return tangent;
}

Vec3f Vertex::getBitangent() const
{
	return bitangent;
}
