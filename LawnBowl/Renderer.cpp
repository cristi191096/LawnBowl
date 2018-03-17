#include "Renderer.h"



Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::Draw(const VertexArray & va, const Shader & shader) const
{
	shader.Bind();
	va.Bind();
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, )
}
