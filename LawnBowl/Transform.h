#pragma once
#include "Vector3D.h"
#include "gtc\matrix_transform.hpp"

class Shader;

class Transform
{
	glm::mat4 model = glm::mat4(1.0);
	glm::mat4 mScale = glm::mat4(1.0);
	glm::mat4 mRot = glm::mat4(1.0);
	glm::mat4 mPosition = glm::mat4(1.0);

	void SetModelMat();

public:

	Vector3D position;
	Vector3D rotation;
	Vector3D scale;
	
	Transform(Vector3D pos, Vector3D rot, Vector3D sc);
	void Translate(Vector3D newPos);
	void Rotate(float angle, Vector3D direction);
	void Scale(Vector3D newScale);
	void SendModelMatrix(Shader* shader);
	~Transform();
};

