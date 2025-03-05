#pragma once
#include <iostream>

class CameraController
{
public:
	float flySpeed = 3.0f;
	float sensitivity = 0.01f;

	float yaw = 0.0f, pitch = 0.0f;

	int prevMouseX = 0, prevMouseY = 0;

	bool firstFrame = true;

	// keybinds
	int forwardKey = GLFW_KEY_W,
		leftKey = GLFW_KEY_A,
		backwardKey = GLFW_KEY_S,
		rightKey = GLFW_KEY_D;
	int upKey = GLFW_KEY_SPACE,
		downKey = GLFW_KEY_LEFT_SHIFT;
	int unlockCamKey = GLFW_KEY_E;


	void moveCamera(GLFWwindow* screen, float deltaTime, Camera* cam)
	{
		//std::cout << cam->lookAt.x << " " << cam->lookAt.y << " " << cam->lookAt.z << std::endl;

		//if (!glfwGetMouseButton(screen, GLFW_MOUSE_BUTTON_2))
		if (!glfwGetKey(screen, unlockCamKey))
		{
			glfwSetInputMode(screen, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			firstFrame = true;
			return;
		}
		glfwSetInputMode(screen, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


		// mouse control
		{
			double mouseX, mouseY;
			glfwGetCursorPos(screen, &mouseX, &mouseY);


			if (firstFrame) {
				firstFrame = false;
				prevMouseX = mouseX;
				prevMouseY = mouseY;
			}

			float mouseDeltaX = (float)(mouseX - prevMouseX);
			float mouseDeltaY = (float)(mouseY - prevMouseY);

			prevMouseX = mouseX;
			prevMouseY = mouseY;

			//Change yaw and pitch (degrees)
			yaw += mouseDeltaX * sensitivity;
			pitch -= mouseDeltaY * sensitivity;
			pitch = glm::clamp(pitch, -89.0f, 89.0f);
		}

		//KEYBOARD MOVEMENT
		{
			float yawRad = glm::radians(yaw);
			float pitchRad = glm::radians(pitch);

			//Construct forward, right, and up vectors
			glm::vec3 forward;
			forward.x = cosf(pitchRad) * sinf(yawRad);
			forward.y = sinf(pitchRad);
			forward.z = cosf(pitchRad) * -cosf(yawRad);
			forward = glm::normalize(forward);

			glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));
			glm::vec3 up = glm::normalize(glm::cross(right, forward));

			//Keyboard movement
			float speed = flySpeed; // glfwGetKey(screen, GLFW_KEY_LEFT_SHIFT) ? sprintMoveSpeed : flySpeed;
			float moveDelta = speed * deltaTime;
			if (glfwGetKey(screen, forwardKey)) {
				cam->position += forward * moveDelta;
			}
			if (glfwGetKey(screen, backwardKey)) {
				cam->position -= forward * moveDelta;
			}
			if (glfwGetKey(screen, rightKey)) {
				cam->position += right * moveDelta;
			}
			if (glfwGetKey(screen, leftKey)) {
				cam->position -= right * moveDelta;
			}
			if (glfwGetKey(screen, upKey)) {
				cam->position += up * moveDelta;
			}
			if (glfwGetKey(screen, downKey)) {
				cam->position -= up * moveDelta;
			}

			//Camera will now look at a position along this forward axis
			cam->lookAt = cam->position + forward;
		}


	};

};
