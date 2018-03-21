#include "Renderer.h"



Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::Draw(const VertexArray & va, const IndexBuffer& ib, const Shader & shader, DrawType type) const
{
	shader.Bind();
	va.Bind();
	if (type == DrawType::ARRAYS) {
	glDrawArrays(GL_TRIANGLE_STRIP, 0, ib.GetCount());

	}
	else if (type == DrawType::ELEMENTS) {
		glDrawElements(GL_TRIANGLE_STRIP, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
