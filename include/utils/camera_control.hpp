#pragma once

class CameraController
{
public:
	float flySpeed;
	float sensitivity;

	float yaw, pitch;

	int prevMouseX, prevMouseY;

	void moveCamera(GLFWwindow* screen, float deltaTime, Camera* cam)
	{

	};

};
