#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CelestialEngine.h"

enum class CameraMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
};

class Camera
{
public:
	Camera(unsigned int scrWidth, unsigned int scrHeight);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

	void ProcessKeyboard(CameraMovement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

	// we store as float to avoid cost of casting per render 
	float scrWidth, scrHeight;

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float yaw;
	float pitch;

	float movementSpeed;
	float mouseSensitivity;
	float zoom;

private:
	void updateCameraVectors();
};
