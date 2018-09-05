#include "vec3f.h"
#include "vec4f.h"

#define PI 3.14159265358979323846

Vec3f::Vec3f() : x(0), y(0), z(0)
{
}

Vec3f::Vec3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vec3f::length() const
{
	return sqrt(x*x + y*y + z*z);

}

float Vec3f::dot(const Vec3f &r)
{
	return this->x * r.getX() + this->y * r.getY() + z * this->z*r.getZ();
}

Vec3f Vec3f::cross(const Vec3f &r)
{
	float x = this->y * r.getZ() - this->z * r.getY();
	float y = this->z * r.getX() - this->x * r.getZ();
	float z = this->x * r.getY() - this->y * r.getX();
		
	return Vec3f(x,y,z);
}

Vec3f Vec3f::normalize()
{
	float length = this->length();
		
	x /= length;
	y /= length;
	z /= length;
		
	return *this;
}

Vec3f Vec3f::rotate(float angle, const Vec3f &axis)
{
	float sinHalfAngle = sin((angle / 2) * (float)PI / 180);
	float cosHalfAngle = cos((angle / 2) * (float)PI / 180);
		
	
	float rX = axis.getX() * sinHalfAngle;
	float rY = axis.getY() * sinHalfAngle;
	float rZ = axis.getZ() * sinHalfAngle;
	float rW = cosHalfAngle;
		
	Vec4f rotation = Vec4f(rX, rY, rZ, rW);
	Vec4f conjugate = rotation.conjugate();
		
	Vec4f w = rotation.mul(*this).mul(conjugate);
	
	x = w.getX();
	y = w.getY();
	z = w.getZ();
		
	return *this;
}


Vec3f Vec3f::add(const Vec3f &r)
	{
		return Vec3f(this->x + r.getX(), this->y + r.getY(), this->z + r.getZ());
	}
	
Vec3f Vec3f::add(float r)
	{
		return Vec3f(this->x + r, this->y + r, this->z + r);
	}
	
Vec3f Vec3f::sub(const Vec3f &r)
	{
		return Vec3f(this->x - r.getX(), this->y - r.getY(), this->z - r.getZ());
	}
	
Vec3f Vec3f::sub(float r)
	{
		return Vec3f(this->x - r, this->y - r, this->z - r);
	}
	
Vec3f Vec3f::mul(const Vec3f &r)
	{
		return Vec3f(this->x * r.getX(), this->y * r.getY(), this->z * r.getZ());
	}
	
Vec3f Vec3f::mul(float x, float y, float z)
	{
		return Vec3f(this->x * x, this->y * y, this->z * z);
	}
	
Vec3f Vec3f::mul(float r)
	{
		return Vec3f(this->x * r, this->y * r, this->z * r);
	}
	
Vec3f Vec3f::div(const Vec3f &r)
	{
		return Vec3f(this->x / r.getX(), this->y / r.getY(), this->z / r.getZ());
	}
	
Vec3f Vec3f::div(float r)
	{
		return Vec3f(this->x / r, this->y / r, this->z / r);
	}


float Vec3f::getX() const
{
		return this->x;
}

void Vec3f::setX(float x)
{
		this->x = x;
}

float Vec3f::getY() const
{
		return this->y;
}

void Vec3f::setY(float y)
{
		this->y = y;
}

float Vec3f::getZ() const
{
		return this->z;
}

void Vec3f::setZ(float z) 
{
		this->z = z;
}

void Vec3f::toString() const
{
}
	
	

