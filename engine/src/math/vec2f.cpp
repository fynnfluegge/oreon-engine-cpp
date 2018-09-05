#include "vec2f.h"

Vec2f::Vec2f() : x(0), y(0)
{
}

Vec2f::Vec2f(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Vec2f::length() const
{
	return (float) sqrt(x*x + y*y);
}
	
float Vec2f::dot(const Vec2f &r)
{
	return x * r.getX() + y * r.getY();
}
	
Vec2f Vec2f::normalize()
{
	float length = this->length();
		
	x /= length;
	y /= length;
		
	return *this;
}
	
Vec2f Vec2f::add(const Vec2f &r)
{
	return Vec2f(x + r.getX(), y + r.getY());
}
	
Vec2f Vec2f::add(float r)
{
	return Vec2f(x + r, y + r);
}
	
Vec2f Vec2f::sub(const Vec2f &r)
{
	return Vec2f(x - r.getX(), y - r.getY());
}
	
Vec2f Vec2f::sub(float r)
{
	return Vec2f(x - r, y - r);
}
	
Vec2f Vec2f::mul(const Vec2f &r)
{
	return Vec2f(x * r.getX(), y * r.getY());
}
	
Vec2f Vec2f::mul(float r)
{
	return Vec2f(x * r, y * r);
}
	
Vec2f Vec2f::div(const Vec2f &r)
{
	return Vec2f(x / r.getX(), y / r.getY());
}
	
Vec2f Vec2f::div(float r)
{
	return Vec2f(x / r, y / r);
}
	

float Vec2f::getX() const
{
	return x;
}

void Vec2f::setX(float x) {
	this->x = x;
}

float Vec2f::getY() const
{
	return y;
}

void Vec2f::setY(float y) {
	this->y = y;
}

void Vec2f::toString() const
{
}