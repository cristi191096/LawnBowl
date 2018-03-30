#include "GameObject.h"
#include <iostream>

std::map<int, bool> GameObject::specialKeys;
std::map<char, bool> GameObject::keys;

GameObject::GameObject(Vector3D pos, std::string tag)
{
	this->tag = tag;
	this->transform = new Transform(pos, Vector3D(0,0,0), Vector3D(1,1,1));
}


GameObject::~GameObject()
{
	delete transform;
	delete mesh;
	delete v_Array;
}

unsigned int GameObject::setupDrawing(unsigned int)
{
	return 0;
}



void GameObject::LoadMesh(std::string path)
{
	OBJLoader loader;

	if (loader.LoadFile(path)) {
		this->mesh = &loader.LoadedMeshes[1];
	}
	else
	{
		std::cout << "Couldn't load the mesh " << std::endl;
	}
}

void GameObject::EnterCollider(Collider * other)
{
}

void GameObject::ExitCollider(Collider * other)
{
}
