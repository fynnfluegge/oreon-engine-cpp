#pragma once

#include "Vec3f.h"

class Vec4f {

public:
	Vec4f();
	Vec4f(float x, float y, float z, float w);
	float length() const;
	Vec4f normalize();
	Vec4f conjugate();
	Vec4f mul(const Vec4f &r);
	Vec4f mul(const Vec3f &r);
	float getX() const;
	float getY() const;
	float getZ() const;
	float getW() const;
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setW(float w);
	void toString() const;

private:
	float x; 
	float y;
	float z;
	float w;
};