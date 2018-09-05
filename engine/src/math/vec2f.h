#pragma once

#include <math.h>

class Vec2f {

public:
	Vec2f();
	Vec2f(float x, float y);
	float length() const;
	float dot(const Vec2f &r);
	Vec2f normalize();
	Vec2f add(const Vec2f &r);
	Vec2f add(float r);
	Vec2f sub(const Vec2f &r);
	Vec2f sub(float r);
	Vec2f mul(const Vec2f &r);
	Vec2f mul(float r);
	Vec2f div(const Vec2f &r);
	Vec2f div(float r);
	float getX() const;
	float getY() const;
	void setX(float x);
	void setY(float y);
	void toString() const;

private:
	float x;
	float y;
};