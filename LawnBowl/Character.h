#pragma once
#include "GameObject.h"

class Character :	public GameObject
{
public:
	Character(std::string modelPath, Vector3D pos, std::string tag, glm::vec4 col);
	void draw();
	void start();
	void update(int deltaTime);

	void EnterCollider(Collider* other);
	void ExitCollider(Collider* other);
	~Character();
};

