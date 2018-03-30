#include "Rect.h"



Rect::Rect(float width, float height, Vector3D pos, std::string tag, glm::vec4 col) : GameObject(pos, tag)
{
	v_Array = new VertexArray();
	v_Array->Bind();
	Vertex v0 = {
		glm::vec3(pos.x()-(width/2), pos.y()-(height/2), pos.z()),
		glm::vec3(0,0,1),
		glm::vec2(0.0, 0.0) };
	verts.push_back(v0);
	Vertex v1 = {
		glm::vec3(pos.x() + width / 2, pos.y() - height / 2, pos.z()),
		glm::vec3(0,0,1),
		glm::vec2(0.0, 0.0) };
	verts.push_back(v1);
	Vertex v2 = {
		glm::vec3(pos.x() + width / 2, pos.y() + height / 2, pos.z()),
		glm::vec3(0,0,1),
		glm::vec2(0.0, 0.0) };
	verts.push_back(v2);
	Vertex v3 = {
		glm::vec3(pos.x() - width / 2, pos.y() + height / 2, pos.z()),
		glm::vec3(0,0,1),
		glm::vec2(0.0, 0.0) };
	verts.push_back(v3);
	inds.push_back(0);
	inds.push_back(1);
	inds.push_back(2);
	inds.push_back(2);
	inds.push_back(3);
	inds.push_back(0);

	this->mesh = new Mesh(verts, inds);
	this->mesh->SetMaterial(col);
}

void Rect::draw()
{
}

void Rect::start()
{
	v_Array->AddBuffer(*mesh->buffer, *mesh->layout);
}

void Rect::update(int deltaTime)
{
}

void Rect::EnterCollider(Collider * other)
{
}

void Rect::ExitCollider(Collider * other)
{
}


Rect::~Rect()
{
}
