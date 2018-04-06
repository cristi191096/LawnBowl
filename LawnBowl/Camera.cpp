#include "Camera.h"

Camera* Camera::instance = new Camera();


//Recalculate the vectors when the Camera's angles are changed.
void Camera::updateCameraVectors()
{
	//Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw))*sin(glm::radians(Pitch));
	Front = glm::normalize(front);

	//Right vector
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}

Camera::Camera(glm::vec3 position , glm::vec3 up , float yaw, float pitch) :
	Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}


Camera::~Camera()
{
	delete instance;
}

void Camera::Perspective(const float& left, const float& right, const float& bottom, const float& top, const float& near, const float& far)
{
	projection = glm::frustum(left, right, bottom, top, near, far);
}

void Camera::ProcessKeyboardInput(Camera_Movement direction, float deltaTime)
{
	float speed = MovementSpeed * (deltaTime/1000);
	if (direction == FORWARD) Position += Front * speed;
	if (direction == BACKWARD) Position -= Front * speed;
	if (direction == LEFT) Position -= Right * speed;
	if (direction == RIGHT) Position += Right * speed;
}

void Camera::ProcessMouseInput(float xOffset, float yOffset, bool clampPitch)
{
	xOffset *= MouseSensitivity;
	yOffset *= MouseSensitivity;

	Yaw += xOffset;
	Pitch += yOffset;

	//If the pitch is out of bounds, the screen gets flipped.
	if (clampPitch) {
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::SetMovementSpeed(const float & newSpeed)
{
	MovementSpeed = newSpeed;
}

void Camera::SetMouseSensitivity(const float & newMS)
{
	MouseSensitivity = newMS;
}

