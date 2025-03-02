#pragma once
#include "GameObject.h"
#include <vector>

class Rect :	public GameObject
{
	float rotAngle;
public:
	Rect(float width, float height, Vector3D pos, std::string tag, glm::vec4 col);
	void draw();
	void start();
	void update(int deltaTime);

	void EnterCollider(Collider* other);
	void ExitCollider(Collider* other);
	~Rect();
};

