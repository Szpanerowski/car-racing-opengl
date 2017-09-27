#pragma once

#include "glm/glm.hpp"

#include "drawing/lighting/CachedLighting.h"

class RenderedObject {

public:

	virtual void render(glm::mat4 view, glm::mat4 projection, CachedLighting* lighting) = 0;
};