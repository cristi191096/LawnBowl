#pragma once


class GameObject;

enum class DrawType {
	ELEMENTS, ARRAYS
};

class Renderer
{
public:
	Renderer();
	~Renderer();
	//TODO here
	void Draw(GameObject* object, DrawType type) const;
	void Clear() const;
};

