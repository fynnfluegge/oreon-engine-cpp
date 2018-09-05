#pragma once

#include <math\Matrix4f.h>
#include <math\Vec3f.h>
#include <math\Vec2f.h>

class Camera{

public:

	static Camera& getInstance();
	void update();
	void move(Vec3f &dir, float amount);
	void rotateY(float angle);
	void rotateX(float angle);

	int getScaleFactor() const;
	Matrix4f getProjectionViewMatrix();
	void setProjection(float fovy, float width, float height, float zNear, float zFar);
	Matrix4f getViewMatrix() const;
	void setViewMatrix(const Matrix4f &viewMatrix);
	Vec3f getPosition() const;
	void setPosition(const Vec3f &position);
	Vec3f getLeft();
	Vec3f getRight();
	Vec3f getForward() const;
	void setForward(Vec3f forward);
	Vec3f getUp() const;
	void setUp(const Vec3f up);
	float getZfar() const;
	float getWidth() const;
	float getHeight() const;

private:

	Camera();

	static Camera instance;
	
	Vec3f position;
	Vec3f forward;
	Vec3f up;
	int scaleFactor;
	Matrix4f viewMatrix;
	Matrix4f projectionMatrix;
	float zNear;
	float zFar;
	float width;
	float height;
	float fovY;

	bool mouselocked;
	Vec2f centerPosition;
	float sensitivity;
};