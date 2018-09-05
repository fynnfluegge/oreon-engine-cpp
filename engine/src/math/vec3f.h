#pragma once

#include <math.h>


class Vec3f{
		
public:
	Vec3f();
	Vec3f(float x, float y, float z);
	float length() const;
	float dot(const Vec3f &r);
	Vec3f cross(const Vec3f &r);
	Vec3f normalize();
	Vec3f rotate(float angle, const Vec3f &axis);
	Vec3f add(const Vec3f &r);
	Vec3f add(float r);
	Vec3f sub(const Vec3f &r);
	Vec3f sub(float r);
	Vec3f mul(const Vec3f &r);
	Vec3f mul(float x, float y, float z);
	Vec3f mul(float r);
	Vec3f div(const Vec3f &r);
	Vec3f div(float r);
	float getX() const;
	float getY() const;
	float getZ() const;
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void toString() const;

private:
	float x;
	float y;
	float z;
};