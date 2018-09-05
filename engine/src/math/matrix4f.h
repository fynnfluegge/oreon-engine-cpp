#pragma once

#include "Vec3f.h"
#include "math\Vec4f.h"
#include <iostream>

class Matrix4f {

public:
	Matrix4f();
	Matrix4f Identity();
	Matrix4f Orthographic();
	Matrix4f Translation(const Vec3f &translation);
	Matrix4f Rotation(const Vec3f &rotation);
	Matrix4f Scaling(const Vec3f &scaling);
	Matrix4f Projection(float fovY, float width, float height, float zNear, float zFar);
	Matrix4f View(Vec3f &forward, Vec3f &up);
	Matrix4f mul(const Matrix4f &r);
	Vec4f mul(const Vec4f &v);
	float get(int x, int y) const;
	void set(int x, int y, float value);
	void toString() const;

private:
	float m[4][4];
};