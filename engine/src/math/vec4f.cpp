#include "vec4f.h"


Vec4f::Vec4f() : x(0), y(0), z(0), w(0)
{
}

Vec4f::Vec4f(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

float Vec4f::length() const
{
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vec4f Vec4f::normalize()
{
	float length = this->length();

	this->x /= length;
	this->y /= length;
	this->z /= length;
	this->w /= length;

	return *this;
}

Vec4f Vec4f::conjugate()
{
	return Vec4f(-this->x, -this->y, -this->z, this->w);
}

Vec4f Vec4f::mul(const Vec4f &r)
{
		float w_ = w * r.getW() - x * r.getX() - y * r.getY() - z * r.getZ();
		float x_ = x * r.getW() + w * r.getX() + y * r.getZ() - z * r.getY();
		float y_ = y * r.getW() + w * r.getY() + z * r.getX() - x * r.getZ();
		float z_ = z * r.getW() + w * r.getZ() + x * r.getY() - y * r.getX();

		return Vec4f(x_, y_, z_, w_);
}

Vec4f Vec4f::mul(const Vec3f &r)
{
		float w_ = -x * r.getX() - y * r.getY() - z * r.getZ();
		float x_ =  w * r.getX() + y * r.getZ() - z * r.getY();
		float y_ =  w * r.getY() + z * r.getX() - x * r.getZ();
		float z_ =  w * r.getZ() + x * r.getY() - y * r.getX();

		return Vec4f(x_, y_, z_, w_);
}

float Vec4f::getX() const{
		return x;
}

void Vec4f::setX(float x) {
		this->x = x;
	}

float Vec4f::getY() const{
		return y;
}

void Vec4f::setY(float y) {
		this->y = y;
}

float Vec4f::getZ() const{
		return z;
}

void Vec4f::setZ(float z) {
		this->z = z;
}

float Vec4f::getW() const{
		return w;
}

void Vec4f::setW(float w) {
		this->w = w;
}

void Vec4f::toString() const
{

}