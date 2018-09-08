#include "camera.h"

Camera Camera::instance;
Camera& Camera::getInstance() {
	return instance;
}

Camera::Camera() : position(0,0,-10), forward(0,-1,1), up(0,1,0), scaleFactor(10), fovY(70), zNear(0.01f), zFar(10000), sensitivity(0.5f) {
	up.normalize();
	forward.normalize();
}

void Camera::update()
{
	float movAmt = scaleFactor * 0.01f;
	float rotAmt = scaleFactor * 0.01f;

	/*if(Input::getHoldingKey(GLFW_KEY_W))
			move(getForward(), movAmt);
	if(Input::getHoldingKey(GLFW_KEY_S))
			move(getForward(), -movAmt);
	if(Input::getHoldingKey(GLFW_KEY_A))
			move(getLeft(), movAmt);
	if(Input::getHoldingKey(GLFW_KEY_D))
		move(getRight(), movAmt);*/

		
	/*setViewMatrix(Matrix4f().View(getForward(), getUp()).mul(
				Matrix4f().Translation(getPosition().mul(-1))));*/
}

void Camera::move(Vec3f &dir, float amount)
{
	Vec3f newPos = position.add(dir.mul(amount));

	setPosition(newPos);
}

void Camera::rotateY(float angle)
{
	Vec3f hAxis = Vec3f(0,1,0).cross(forward).normalize();

	forward.rotate(angle, Vec3f(0,1,0)).normalize();

	up = forward.cross(hAxis).normalize();
}

void Camera::rotateX(float angle)
{
	Vec3f hAxis = Vec3f(0,1,0).cross(forward).normalize();

	forward.rotate(angle, hAxis).normalize();

	up = forward.cross(hAxis).normalize();
}

Vec3f Camera::getLeft()
{
	Vec3f left = forward.cross(up);
	left.normalize();
	return left;
}

Vec3f Camera::getRight()
{
	Vec3f right = up.cross(forward);
	right.normalize();
	return right;
}

int Camera::getScaleFactor() const
{
	return scaleFactor;
}

void setScaleFactor(int scaleFactor)
{
	scaleFactor = scaleFactor;
}

Matrix4f Camera::getProjectionViewMatrix()
{
	return this->projectionMatrix.mul(viewMatrix);
}

void Camera::setProjection(float fovY, float width, float height, float zNear, float zFar)
{
	this->fovY = fovY;
	this->width = width;
	this->height = height;
	this->zNear = zNear;
	this->zFar = zFar;
}

Matrix4f Camera::getViewMatrix() const
{
	return viewMatrix;
}

void Camera::setViewMatrix(const Matrix4f &m)
{
	viewMatrix = m;
}

Vec3f Camera::getPosition() const
{
	return position;
}

void Camera::setPosition(const Vec3f &v)
{
	position = v;
}

Vec3f Camera::getForward() const
{
	return forward;
}

void Camera::setForward(Vec3f forward)
{
	this->forward = forward;
}

Vec3f Camera::getUp() const
{
	return up;
}

void Camera::setUp(Vec3f up) 
{
	this->up = up;
}
	
float Camera::getZfar() const
{
	return zFar;
}

float Camera::getWidth() const
{
	return width;
}

float Camera::getHeight() const
{
	return height;
}