#pragma once

#include "math\vec3f.h"
#include "math\vec2f.h"

enum VertexLayout
{
	POS_NORMAL_UV_TAN_BITAN,
	POS_NORMAL,
	POS_UV,
	POS,
	POS_NORMAL_UV,
	POS2D,
	POS2D_UV
};

class Vertex {
public:
	Vertex();
	Vertex(Vec3f pos);
private:
	Vec3f position;
	Vec3f normal;
	Vec2f texCoord;
	Vec3f tangent;
	Vec3f bitangent;
};