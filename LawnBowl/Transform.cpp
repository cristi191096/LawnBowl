#include "Transform.h"
#include "Material.h"


Transform::Transform(Vector3D pos, Vector3D rot, Vector3D sc)
{
	this->position = pos;
	this->rotation = rot;
	this->scale = sc;
	this->Translate(position);
}

void Transform::Translate(Vector3D newPos)
{
	modelView = glm::mat4(1.0);
	modelView = glm::translate( modelView, 
		glm::vec3(newPos.x(), newPos.y(), newPos.z())); 
	
	
}

void Transform::Rotate(float angle, Vector3D direction)
{
	modelView = glm::mat4(1.0);
	modelView = glm::translate(modelView,
		glm::vec3(-position.x(), -position.y(), -position.z()));
	modelView = glm::rotate(modelView, angle, glm::vec3(direction.x(), direction.y(), direction.z()));
	modelView = glm::translate(modelView,
		glm::vec3(position.x(), position.y(), position.z()));
	
}

void Transform::Scale(Vector3D newScale)
{
	modelView = glm::mat4(1.0);
	modelView = glm::scale(modelView, glm::vec3(newScale.x(), newScale.y(), newScale.z()));
	
}



Transform::~Transform()
{
}
