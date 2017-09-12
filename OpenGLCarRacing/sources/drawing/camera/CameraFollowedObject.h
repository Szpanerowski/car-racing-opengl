#pragma once

#include "glm/mat4x4.hpp"

class CameraFollowedObject {

public:

	virtual glm::vec3 getPosition() = 0;
	virtual glm::vec3 getFaceVector() = 0;
};