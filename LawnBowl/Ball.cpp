#include "Ball.h"


Ball::Ball(int rad, Vector3D pos, std::string tag) : GameObject(pos, tag)
{
	this->mesh = new Mesh();
	this->mesh->CreateSphere(rad, 10, 10);
}



void Ball::start()
{
	VertexBufferLayout layout;
	layout.Push<Vertex>(this->mesh->vertices.size());
	v_Array = new VertexArray();

	v_Array->AddBuffer(*mesh->buffer, layout);

}

void Ball::update(int deltaTime)
{
}

void Ball::EnterCollider(Collider * other)
{
}

void Ball::ExitCollider(Collider * other)
{
}


Ball::~Ball()
{
}
