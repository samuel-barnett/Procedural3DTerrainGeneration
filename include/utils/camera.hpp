#pragma once
#include "terrain_gen/mesh.hpp"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"


class Camera
{
public:
	glm::vec3 position;
	glm::vec3 lookAt;

	float FOV = 90;
	float near;
	float far;
	float aspectRatio;

	// orthographic
	bool orthographic = false;
	float orthoHeight = 6.0f;

	inline glm::mat4 viewMatrix() const
	{
		glm::vec3 toTarget = glm::normalize(lookAt - position);
		glm::vec3 up = glm::vec3(0, 1, 0);
		//If camera is aligned with up vector, choose a new one
		if (glm::abs(glm::dot(toTarget, up)) >= 1.0f - glm::epsilon<float>()) {
			up = glm::vec3(0, 0, 1);
		}
		return glm::lookAt(position, lookAt, up);
	}
	inline glm::mat4 projectionMatrix()const {

		if (orthographic) {

			float width = orthoHeight * aspectRatio;
			float right = width / 2;
			float left = -right;
			float top = orthoHeight / 2;
			float bottom = -top;
			return glm::ortho(left, right, bottom, top, near, far);
		}
		else {
			return glm::perspective(glm::radians(FOV), aspectRatio, near, far);
		}
	}

};
