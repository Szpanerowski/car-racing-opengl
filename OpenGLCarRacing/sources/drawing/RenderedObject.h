#pragma once

#include "glm/glm.hpp"

class RenderedObject {

public:

	virtual void render(glm::mat4 view, glm::mat4 projection) = 0;
};