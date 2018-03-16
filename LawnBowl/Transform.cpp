#include "Transform.h"



Transform::Transform(Vector3D pos, Vector3D rot, Vector3D sc)
{
	this->position = pos;
	this->rotation = rot;
	this->scale = sc;
}

void Transform::Translate(Vector3D newPos)
{

	modelView = glm::translate( modelView, 
		glm::vec3(newPos.x(), newPos.y(), newPos.z())); 
}

void Transform::Rotate(float angle, Vector3D direction)
{

}

void Transform::Scale(Vector3D newScale)
{
	modelView = glm::scale(modelView, glm::vec3(newScale.x(), newScale.y(), newScale.z()));
}



Transform::~Transform()
{
}
