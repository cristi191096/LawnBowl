#include "Camera.h"

Camera* Camera::instance = new Camera();

Camera::Camera()
{
	view = glm::mat4(1.0);
	projection = glm::mat4(1.0);
}


Camera::~Camera()
{
	delete instance;
}

void Camera::Perspective(const float& left, const float& right, const float& bottom, const float& top, const float& near, const float& far)
{
	projection = glm::frustum(left, right, bottom, top, near, far);
}

void Camera::LookAt(const glm::vec3 & lookPos, const glm::vec3 & diretion)
{
	view = glm::mat4(1.0);
	view = glm::lookAt(position, lookPos, diretion);
}
