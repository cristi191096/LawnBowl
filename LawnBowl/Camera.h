#pragma once
#include <glm.hpp>
#include "gtc\matrix_transform.hpp"

class Camera
{
	glm::mat4 view;
	glm::mat4 projection;

public:
	static Camera* instance;
	glm::vec3 position = glm::vec3(0,0,-1);
	Camera();
	~Camera();
	void Perspective(const float& left, const float& right, const float& bottom, const float& top, const float& near, const float& far);
	void LookAt(const glm::vec3& lookPos, const glm::vec3& diretion);

	inline glm::mat4 GetView() const { return view; }
	inline glm::mat4 GetProjection() const { return projection; }
};

