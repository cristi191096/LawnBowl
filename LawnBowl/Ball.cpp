#include "Ball.h"


Ball::Ball(int rad, Vector3D pos, std::string tag, glm::vec4 col) : GameObject(pos, tag, col)
{
	
	CreateSphere(rad, 10, 10);
	this->model = new Model();
	this->model->AddNewMesh(verts, inds);
	this->model->meshes[0].SetMaterial(col);
	
}

void Ball::CreateSphere(int radius, int stacks, int slices)
{


	for (int i = 0; i <= stacks; ++i) {

		GLfloat V = i / (float)stacks;
		GLfloat phi = V * glm::pi<float>();

		// Loop Through Slices
		for (int j = 0; j <= slices; ++j) {

			GLfloat U = j / (float)slices;
			GLfloat theta = U * (glm::pi<float>() * 2);

			// Calc The Vertex Positions
			GLfloat x = cosf(theta) * sinf(phi);
			GLfloat y = cosf(phi);
			GLfloat z = sinf(theta) * sinf(phi);

			Vertex vert;

			vert.position = glm::vec3(x * radius, y * radius + 6.0, z * radius);
			vert.normal = glm::vec3(x, y, z); ///Sphere normals
			vert.uv = glm::vec2(0.0, 0.0);
			verts.push_back(vert);


		}
	}


	// Calc The Index Positions
	for (int i = 0; i < slices * stacks + slices; ++i) {

		inds.push_back(i);

		inds.push_back(i + slices + 1);

		inds.push_back(i + slices);


		inds.push_back(i + slices + 1);

		inds.push_back(i);

		inds.push_back(i + 1);

	}




	//meshMaterial->PushMaterial(layout);

}


void Ball::draw()
{
	transform->Translate(Vector3D(0, 0, 0));
	transform->SendModelMatrix(this->model->meshes[0].meshMaterial->shader);
}

void Ball::start()
{	
	
	
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
