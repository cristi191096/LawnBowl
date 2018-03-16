#pragma once
#include "Vector3D.h"
#include "gtc\matrix_transform.hpp"


class Transform
{
public:
	glm::mat4 modelView = glm::mat4(1.0);

	Vector3D position;
	Vector3D rotation;
	Vector3D scale;
	
	Transform(Vector3D pos, Vector3D rot, Vector3D sc);
	void Translate(Vector3D newPos);
	void Rotate(float angle, Vector3D direction);
	void Scale(Vector3D newScale);
	~Transform();
};

