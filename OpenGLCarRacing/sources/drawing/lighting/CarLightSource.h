#pragma once

#include "glm/vec3.hpp"

struct CarLightSource {

	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 color;
	float angle;

	CarLightSource(glm::vec3 position, glm::vec3 direction, float angle, glm::vec3 color = glm::vec3(1, 1, 1)) {

		this->position = position;
		this->direction = direction;
		this->color = color;
		this->angle = angle;
	}
};