#pragma once



#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>

#pragma comment(lib, "glew32d.lib") 
#endif

#include "Collider.h"
#include "Transform.h"
#include "OBJLoader.h"
#include <map>

class GameObject
{
public:
	static std::map<int, bool> GameObject::specialKeys;
	static std::map<char, bool> GameObject::keys;
	Transform* transform;
	Mesh* mesh;

	GameObject(Vector3D);
	~GameObject();

	virtual unsigned int setupDrawing(unsigned int);
	virtual void drawScene();

	virtual void start() = 0;
	virtual void update(int deltaTime) = 0;

	virtual void EnterCollider(Collider* other);
	virtual void ExitCollider(Collider* other);
};

