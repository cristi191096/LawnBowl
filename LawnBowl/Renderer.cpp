#include "Renderer.h"
#include "GameObject.h"



Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::Draw(GameObject* object, DrawType type) const
{
	
	object->v_Array->Bind();
	
	if (type == DrawType::ARRAYS) {
	glDrawArrays(GL_TRIANGLE_STRIP, 0, object->mesh->indexBuffer->GetCount());

	}
	else if (type == DrawType::ELEMENTS) {
		glDrawElements(GL_TRIANGLE_STRIP, object->mesh->indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
