#include "Renderer.h"
#include "GameObject.h"
#include "VertexArray.h"
#include "IndexBuffer.h"


Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::Draw(VertexArray* va, IndexBuffer* ib, int vertsNum, DrawType type) 
{

	//object->v_Array->Bind();
	/*object->mesh->indexBuffer->Bind();
	object->mesh->buffer->Bind();*/
	va->Bind();
	ib->Bind();
	
	if (type == DrawType::ARRAYS) {
	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertsNum);

	}
	else if (type == DrawType::ELEMENTS) {
		glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
	va->Unbind();
	ib->Unbind();
	//object->v_Array->Unbind();
	/*object->mesh->indexBuffer->Unbind();
	object->mesh->buffer->Unbind();*/
}

void Renderer::Clear()
{
	glClearColor(0.5, 0.1, 0.12, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
