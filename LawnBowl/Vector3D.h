#pragma once

#include "glm.hpp"

class Vector3D
{
	glm::vec3* vector;
	
public:
	float x();
	float y();
	float z();

	Vector3D();
	Vector3D(float, float, float);
	float DotProduct(Vector3D&);
	float Length();
	void Normalise();
	void Reflect(Vector3D&);
	Vector3D CrossProduct(Vector3D&);
	Vector3D operator+(const Vector3D& other);
	Vector3D operator-(const Vector3D& other);
	bool operator==(const Vector3D& other);
	Vector3D operator*(const float& scalar);
	void operator+=(const Vector3D& other);
	void operator-=(const Vector3D& other);

	~Vector3D();
};

