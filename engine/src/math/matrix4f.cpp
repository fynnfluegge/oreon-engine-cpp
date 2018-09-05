#include "matrix4f.h"
#include <scene\camera.h>

constexpr auto PI = 3.14159265358979323846f;

Matrix4f::Matrix4f()
{
}

Matrix4f Matrix4f::Identity()
{
		m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
		m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
		m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
		m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
	
		return *this;
}

Matrix4f Matrix4f::Orthographic()
{
		m[0][0] = 2/Camera::getInstance().getWidth(); 	m[0][1] = 0; 									m[0][2] = 0; m[0][3] = -1;
		m[1][0] = 0;		 							m[1][1] = 2/Camera::getInstance().getHeight();	m[1][2] = 0; m[1][3] = -1;
		m[2][0] = 0; 									m[2][1] = 0; 									m[2][2] = 1; m[2][3] =  0;
		m[3][0] = 0; 									m[3][1] = 0; 									m[3][2] = 0; m[3][3] =  1;
		
		return *this;
}

Matrix4f Matrix4f::Translation(const Vec3f &translation)
{
		m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = translation.getX();
		m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = translation.getY();
		m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = translation.getZ();
		m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
	
		return *this;
}

Matrix4f Matrix4f::Rotation(const Vec3f &rotation)
{
		Matrix4f rx = Matrix4f();
		Matrix4f ry = Matrix4f();
		Matrix4f rz = Matrix4f();
		
		float x = rotation.getX() * PI / 180.0f;
		float y = rotation.getY() * PI / 180.0f;
		float z = rotation.getZ() * PI / 180.0f;
		
		rz.m[0][0] = cos(z);			 rz.m[0][1] = -sin(z); 				 rz.m[0][2] = 0; 				   rz.m[0][3] = 0;
		rz.m[1][0] = sin(z);			 rz.m[1][1] =  cos(z);  			 rz.m[1][2] = 0; 				   rz.m[1][3] = 0;
		rz.m[2][0] = 0; 				 rz.m[2][1] = 0; 				   	 rz.m[2][2] = 1; 				   rz.m[2][3] = 0;
		rz.m[3][0] = 0; 				 rz.m[3][1] = 0; 				   	 rz.m[3][2] = 0; 				   rz.m[3][3] = 1;
		
		rx.m[0][0] = 1; 				 rx.m[0][1] = 0;					 rx.m[0][2] = 0; 				   rx.m[0][3] = 0;
		rx.m[1][0] = 0; 				 rx.m[1][1] = cos(x); 				 rx.m[1][2] = -sin(x);			   rx.m[1][3] = 0;
		rx.m[2][0] = 0; 				 rx.m[2][1] = sin(x); 				 rx.m[2][2] = cos(x);              rx.m[2][3] = 0;
		rx.m[3][0] = 0; 				 rx.m[3][1] = 0; 				 	 rx.m[3][2] = 0;				   rx.m[3][3] = 1;
		
		ry.m[0][0] = cos(y);			 ry.m[0][1] = 0; 					 ry.m[0][2] = sin(y);			   ry.m[0][3] = 0;
		ry.m[1][0] = 0; 				 ry.m[1][1] = 1; 				 	 ry.m[1][2] = 0; 				   ry.m[1][3] = 0;
		ry.m[2][0] = -sin(y);			 ry.m[2][1] = 0;					 ry.m[2][2] = cos(y);			   ry.m[2][3] = 0;
		ry.m[3][0] = 0; 				 ry.m[3][1] = 0; 					 ry.m[3][2] = 0; 				   ry.m[3][3] = 1;
	

		Matrix4f temp = rz.mul(ry.mul(rx));
		
		std::memcpy(m,temp.m, 16 * sizeof(float));
		
		return *this;
}

Matrix4f Matrix4f::Scaling(const Vec3f &scaling)
{
		m[0][0] = scaling.getX(); 	m[0][1] = 0; 				m[0][2] = 0; 				m[0][3] = 0;
		m[1][0] = 0; 			 	m[1][1] = scaling.getY();	m[1][2] = 0; 				m[1][3] = 0;
		m[2][0] = 0; 				m[2][1] = 0; 				m[2][2] = scaling.getZ(); 	m[2][3] = 0;
		m[3][0] = 0; 				m[3][1] = 0; 				m[3][2] = 0; 				m[3][3] = 1;
	
		return *this;
}

Matrix4f Matrix4f::Projection(float fovy, float width, float height, float zNear, float zFar)
{
	float tanFOV = tan((fovy/2) * PI / 180.0f);
		
	m[0][0] = 1.0f / (tanFOV*(width/height));	m[0][1] = 0; 				m[0][2] = 0; 							m[0][3] = 0;
	m[1][0] = 0; 				   	  			m[1][1] = 1.0f / tanFOV;  	m[1][2] = 0; 							m[1][3] = 0;
	m[2][0] = 0; 				      			m[2][1] = 0; 				m[2][2] = (-zNear-zFar)/(zNear-zFar);	m[2][3] = 2 * zFar * zNear / (zNear-zFar);
	m[3][0] = 0; 				      			m[3][1] = 0; 				m[3][2] = 1; 							m[3][3] = 0;
	
	return *this;
}

Matrix4f Matrix4f::View(Vec3f &forward, Vec3f &up)
{
	Vec3f f = forward.normalize();
	Vec3f r = up.normalize().cross(f);
	Vec3f u = f.cross(r);
		
	m[0][0] = r.getX(); m[0][1] = r.getY(); m[0][2] = r.getZ(); m[0][3] = 0;
	m[1][0] = u.getX(); m[1][1] = u.getY(); m[1][2] = u.getZ(); m[1][3] = 0;
	m[2][0] = f.getX();	m[2][1] = f.getY(); m[2][2] = f.getZ(); m[2][3] = 0;
	m[3][0] = 0; 		m[3][1] = 0; 		m[3][2] = 0; 		m[3][3] = 1;
	
	return *this;
}

Matrix4f Matrix4f::mul(const Matrix4f &r){
		
		Matrix4f res = Matrix4f();
		
		for (int i=0; i<4; i++)
		{
			for (int j=0; j<4; j++)
			{
				res.set(i, j, m[i][0] * r.get(0, j) + 
							  m[i][1] * r.get(1, j) +
							  m[i][2] * r.get(2, j) +
							  m[i][3] * r.get(3, j));
			}
		}
		
		return res;
}

Vec4f Matrix4f::mul(const Vec4f &v)
	{
		Vec4f res = Vec4f(0,0,0,0);
		res.setX(m[0][0] * v.getX() + m[0][1] * v.getY() + m[0][2] * v.getZ() + m[0][3] * v.getW());
		res.setY(m[1][0] * v.getX() + m[1][1] * v.getY() + m[1][2] * v.getZ() + m[1][3] * v.getW());
		res.setZ(m[2][0] * v.getX() + m[2][1] * v.getY() + m[2][2] * v.getZ() + m[2][3] * v.getW());
		res.setW(m[3][0] * v.getX() + m[3][1] * v.getY() + m[3][2] * v.getZ() + m[3][3] * v.getW());
		
		return res;
	}
	
float Matrix4f::get(int x, int y) const
	{
		return m[x][y];
	}
	
void Matrix4f::set(int x, int y, float value)
	{
		m[x][y] = value;
	}

void Matrix4f::toString() const
{
	
}