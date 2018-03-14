#include "GameObject.h"

std::map<int, bool> GameObject::specialKeys;
std::map<char, bool> GameObject::keys;

GameObject::GameObject(Vector3D pos)
{
	this->transform = new Transform(pos, Vector3D(0,0,0), Vector3D(1,1,1));
}


GameObject::~GameObject()
{
}

unsigned int GameObject::setupDrawing(unsigned int)
{
	return 0;
}

void GameObject::drawScene()
{
}

void GameObject::EnterCollider(Collider * other)
{
}

void GameObject::ExitCollider(Collider * other)
{
}
