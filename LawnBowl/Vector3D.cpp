#include "Vector3D.h"



float Vector3D::x()
{
	return this->vector->x;
}

float Vector3D::y()
{
	return this->vector->y;
}

float Vector3D::z()
{
	return this->vector->z;
}

Vector3D::Vector3D()
{
	vector = new glm::vec3(0, 0, 0);

	
}

Vector3D::Vector3D(float _x, float _y, float _z)
{
	vector = new glm::vec3(_x, _y, _z);

	
}

float Vector3D::DotProduct(Vector3D& other)
{
	float dotProduct = glm::dot(*(this->vector), *(other.vector));
	
	return dotProduct;
}

float Vector3D::Length()
{
	return vector->length();
}

void Vector3D::Normalise()
{
	glm::normalize(*(this->vector));
	
}

void Vector3D::Reflect(Vector3D& normal)
{
	glm::reflect(*(this->vector), *(normal.vector));
	
}

Vector3D Vector3D::CrossProduct(Vector3D& other)
{
	glm::vec3 crossProduct = glm::cross(*(this->vector), *(other.vector));

	return Vector3D(crossProduct.x, crossProduct.y, crossProduct.z);
}

Vector3D Vector3D::operator+(const Vector3D & other)
{
	Vector3D sum(
		this->vector->x + other.vector->x,
		this->vector->y + other.vector->y,
		this->vector->z + other.vector->z
	);

	return sum;
}

Vector3D Vector3D::operator-(const Vector3D & other)
{
	Vector3D dif(
		this->vector->x - other.vector->x,
		this->vector->y - other.vector->y,
		this->vector->z - other.vector->z
	);

	return dif;
}

bool Vector3D::operator==(const Vector3D & other)
{
	return this->vector == other.vector;
}

Vector3D Vector3D::operator*(const float & scalar)
{
	Vector3D mult(
		this->vector->x * scalar,
		this->vector->y * scalar,
		this->vector->z * scalar
	);
	return mult;
}

void Vector3D::operator+=(const Vector3D & other)
{
	//this->vector += other.vector;
	this->vector->operator+=(*(other.vector));
	
}

void Vector3D::operator-=(const Vector3D & other)
{
	this->vector->operator-=(*(other.vector));
	
}


Vector3D::~Vector3D()
{
}
