#pragma once
#include "GameObject.h"

class Ball : public GameObject
{
public:
	Ball(int rad, Vector3D pos, std::string tag);

	void draw();
	void start();
	void update(int deltaTime);

	void EnterCollider(Collider* other);
	void ExitCollider(Collider* other);
	~Ball();
};

