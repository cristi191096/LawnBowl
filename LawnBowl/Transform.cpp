#include "Transform.h"
#include "Material.h"


void Transform::SetModelMat()
{
	model = mPosition * mRot * mScale;
}

Transform::Transform(Vector3D pos, Vector3D rot, Vector3D sc)
{
	this->position = pos;
	this->rotation = rot;
	this->scale = sc;
	this->Translate(position);
}

void Transform::Translate(Vector3D newPos)
{
	mPosition = glm::mat4(1.0);
	mPosition = glm::translate(mPosition,
		glm::vec3(newPos.x(), newPos.y(), newPos.z())); 
}

void Transform::Rotate(float angle, Vector3D direction)
{
	mPosition = glm::mat4(1.0);
	mPosition = glm::translate(mPosition,
		glm::vec3(-position.x(), -position.y(), -position.z()));
	mRot = glm::rotate(mRot, glm::radians(angle), glm::vec3(direction.x(), direction.y(), direction.z()));
	mPosition = glm::translate(mPosition,
		glm::vec3(position.x(), position.y(), position.z()));
	
}

void Transform::Scale(Vector3D newScale)
{
	mScale = glm::mat4(1.0);
	mScale = glm::scale(mScale, glm::vec3(newScale.x(), newScale.y(), newScale.z()));
	
}

void Transform::SendModelMatrix(Shader * shader)
{
	shader->SetUniformMat4("u_ModelMat", model);
}

Transform::~Transform()
{
}
