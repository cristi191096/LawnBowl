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
	object->mesh->indexBuffer->Bind();
	object->mesh->buffer->Bind();
	
	if (type == DrawType::ARRAYS) {
	glDrawArrays(GL_TRIANGLE_STRIP, 0, object->mesh->vertices.size());

	}
	else if (type == DrawType::ELEMENTS) {
		glDrawElements(GL_TRIANGLE_STRIP, object->mesh->indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	object->v_Array->Unbind();
	object->mesh->indexBuffer->Unbind();
	object->mesh->buffer->Unbind();
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
