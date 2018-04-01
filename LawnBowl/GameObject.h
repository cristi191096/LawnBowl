#pragma once

#include "Collider.h"
#include "Transform.h"
#include "OBJLoader.h"
#include "Model.h"
#include <map>
#include <vector>

class GameObject
{
protected:
	std::vector<Vertex> verts;
	std::vector<unsigned int> inds;

public:
	
	static std::map<int, bool> GameObject::specialKeys;
	static std::map<char, bool> GameObject::keys;
	std::string tag;
	Transform* transform;
	Model* model = nullptr;

	GameObject(Vector3D, std::string tag, glm::vec4 col);
	virtual ~GameObject();

	virtual unsigned int setupDrawing(unsigned int);

	virtual void draw() = 0;	

	virtual void start() = 0;
	virtual void update(int deltaTime) = 0;

	void LoadMesh(std::string path);

	virtual void EnterCollider(Collider* other);
	virtual void ExitCollider(Collider* other);
};

