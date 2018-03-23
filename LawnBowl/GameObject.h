#pragma once

#include "Collider.h"
#include "Transform.h"
#include "OBJLoader.h"
#include <map>

class GameObject
{
protected:
	

public:
	VertexArray* v_Array;
	static std::map<int, bool> GameObject::specialKeys;
	static std::map<char, bool> GameObject::keys;
	std::string tag;
	Transform* transform;
	Mesh* mesh = nullptr;

	GameObject(Vector3D, std::string tag);
	virtual ~GameObject();

	virtual unsigned int setupDrawing(unsigned int);

	virtual void draw() = 0;	

	virtual void start() = 0;
	virtual void update(int deltaTime) = 0;

	void LoadMesh(std::string path);

	virtual void EnterCollider(Collider* other);
	virtual void ExitCollider(Collider* other);
};

