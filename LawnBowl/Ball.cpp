#include "Ball.h"


Ball::Ball(int rad, Vector3D pos, std::string tag, glm::vec4 col) : GameObject(pos, tag)
{
	
	v_Array = new VertexArray();
	v_Array->Bind();
	this->mesh = new Mesh();
	this->mesh->SetMaterial(col);
	this->mesh->CreateSphere(rad, 10, 10);
}



void Ball::draw()
{
	transform->Translate(Vector3D(0, 0, 0));
	mesh->meshMaterial->shader->SetUniformMat4("u_ModelViewMat", transform->modelView);
}

void Ball::start()
{	
	v_Array->AddBuffer(*mesh->buffer, *mesh->layout);
	
}

void Ball::update(int deltaTime)
{
}

void Ball::EnterCollider(Collider* other)
{
}

void Ball::ExitCollider(Collider* other)
{
}


Ball::~Ball()
{

}
