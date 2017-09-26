#pragma once

#include "glm/vec3.hpp"

struct PhysicalModelMovement {

	glm::vec3 velocity;
	glm::vec3 rotation;

	PhysicalModelMovement(glm::vec3 velocity, glm::vec3 rotation);
};