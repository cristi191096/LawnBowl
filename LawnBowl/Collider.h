#pragma once

#include "Vector3D.h"
#include <string>

class Collider
{
public:
	Vector3D* colliderCentre = nullptr;
	std::string tag = "Untagged";

	virtual bool collisionEnter(Collider* other) = 0; ///<pure virtual function. very collider must implement collidesWith, which calculates whethwer this collider collides with other.
	virtual bool collisionExit(Collider* other) = 0;
	/* Every collider must implement the following pure virtual function or otherwise cause a compile error.*/
	virtual float minX() = 0; ///<Lowest x value for the collider. Must override in inherited classes.
	virtual float maxX() = 0; ///<Highest x value for the collider. Must override in inherited classes.
	virtual float minY() = 0; ///<Lowest y value for the collider. Must override in inherited classes.
	virtual float maxY() = 0; ///<Highest y value for the collider. Must override in inherited classes.
	virtual float minZ() = 0; ///<Lowest z value for the collider. Must override in inherited classes.
	virtual float maxZ() = 0; ///<Highest z value for the collider. Must override in inherited classes.
	virtual float radius() = 0;
	virtual void draw() = 0;

};


