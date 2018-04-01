#include "Rect.h"



Rect::Rect(float width, float height, Vector3D pos, std::string tag, glm::vec4 col) : GameObject(pos, tag, col)
{
	
	Vertex v0 = {
		glm::vec3(pos.x()-(width/2), pos.y()-(height/2), pos.z()),
		glm::vec3(0,0,1),
		glm::vec2(0.0, 0.0) };
	verts.push_back(v0);
	Vertex v1 = {
		glm::vec3(pos.x() + width / 2, pos.y() - height / 2, pos.z()),
		glm::vec3(0,0,1),
		glm::vec2(1.0, 0.0) };
	verts.push_back(v1);
	Vertex v2 = {
		glm::vec3(pos.x() + width / 2, pos.y() + height / 2, pos.z()),
		glm::vec3(0,0,1),
		glm::vec2(1.0, 1.0) };
	verts.push_back(v2);
	Vertex v3 = {
		glm::vec3(pos.x() - width / 2, pos.y() + height / 2, pos.z()),
		glm::vec3(0,0,1),
		glm::vec2(0.0, 1.0) };
	verts.push_back(v3);
	inds.push_back(0);
	inds.push_back(1);
	inds.push_back(2);
	inds.push_back(2);
	inds.push_back(3);
	inds.push_back(0);

	this->model = new Model();
	this->model->AddNewMesh(verts, inds);
	for (unsigned int i = 0; i < model->meshes.size(); i++) {
		this->model->meshes[i].SetMaterial(col);
		this->model->meshes[i].meshMaterial->SetDiffuseTexture("Resources/Textures/front.png");
	}
}

void Rect::draw()
{
	transform->Rotate(rotAngle, Vector3D(0.0, 0.0, 1.0));
	//transform->Scale(Vector3D(0.0, rotAngle, 0.0));
	transform->SendModelMatrix(this->model->meshes[0].meshMaterial->shader);
}

void Rect::start()
{
	
}

void Rect::update(int deltaTime)
{
	if (specialKeys[GLUT_KEY_RIGHT]) {
		rotAngle += 5.0;
		
		std::cout << "Right key pressed" << rotAngle << std::endl;
		
	}
	//transform->Rotate(45 , Vector3D(0, 0, 1));
	//transform->SendModelMatrix(this->mesh->meshMaterial->shader);
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
