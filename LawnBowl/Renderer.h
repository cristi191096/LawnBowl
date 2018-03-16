#pragma once

#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>

#pragma comment(lib, "glew32d.lib") 
#endif

class Renderer
{
public:
	Renderer();
	~Renderer();
	//TODO here
	void Draw();
};

