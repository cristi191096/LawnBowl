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

class GameObject
{
public:
	GameObject();
	~GameObject();
};

