#pragma once
#include <glm.hpp>
#include "gtc\matrix_transform.hpp"


//Possible options for the camera to move. (Rather than set a specific input)
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;

class Camera
{
	
	float Yaw;
	float Pitch;
	// Camera options
	float MovementSpeed;
	float MouseSensitivity;

	//glm::mat4 view;
	glm::mat4 projection;

	void updateCameraVectors();

public:
	static Camera* instance;

	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;


	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	~Camera();
	void Perspective(const float& left, const float& right, const float& bottom, const float& top, const float& near, const float& far);
	
	void ProcessKeyboardInput(Camera_Movement driection, float deltaTime);
	void ProcessMouseInput(float xOffset, float yOffset, bool clampPitch = true);
	void SetMovementSpeed(const float& newSpeed);
	void SetMouseSensitivity(const float& newMS);

	inline float GetPitch() const { return Pitch; }
	inline float GetYaw() const { return Yaw; }
	inline float GetMovementSpeed() const { return MovementSpeed; }
	inline float GetMouseSensitivity() const { return MouseSensitivity; }
	 glm::mat4 GetView() { return glm::lookAt(Position, Position + Front, Up); }
	 glm::mat4 GetProjection() { return projection; }
};

