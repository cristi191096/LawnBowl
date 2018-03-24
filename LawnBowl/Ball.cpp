#include "Ball.h"


Ball::Ball(int rad, Vector3D pos, std::string tag) : GameObject(pos, tag)
{
	v_Array = new VertexArray();
	v_Array->Bind();
	this->mesh = new Mesh();
	this->mesh->SetMaterial(glm::vec4(0, 1, 0, 1));
	this->mesh->CreateSphere(rad, 10, 10);
}



void Ball::draw()
{
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
