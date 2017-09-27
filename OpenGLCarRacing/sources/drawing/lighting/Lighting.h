#pragma once

#include <vector>
#include "glm/vec3.hpp"

#include "drawing/lighting/CarLightSource.h"

class Lighting
{

private:

	std::vector<CarLightSource> carLightSources;
	glm::vec3 globalAmbient;
	glm::vec3 viewerPosition;

public:
	
	Lighting(glm::vec3 globalAmbient);

	void addCarLightSource(CarLightSource carLightSource);
	
	std::vector<CarLightSource> getCarLightSources();
	void setCarLightSources(std::vector<CarLightSource> carLightSources);

	glm::vec3 getViewerPosition();
	void setViewerPosition(glm::vec3 viewerPosition);

	glm::vec3 getGlobalAmbient();
	void setGlobalAmbient(glm::vec3 globalAmbient);
};

