#pragma once

#include "drawing/lighting/Lighting.h"
#include "drawing/lighting/CarLightSource.h"

#include "glm/vec3.hpp"
#include <vector>

struct CachedLighting {

	int lightSourcesCount;
	glm::vec3 globalAmbient;
	glm::vec3 viewerPosition;

	std::vector<float> lightPositions;
	std::vector<float> lightDirections;
	std::vector<float> lightColors;
	std::vector<float> lightAngles;

	CachedLighting(Lighting* lighting) {

		std::vector<CarLightSource> lightSources = lighting->getCarLightSources();

		lightSourcesCount = lightSources.size();
		globalAmbient = lighting->getGlobalAmbient();
		viewerPosition = lighting->getViewerPosition();

		for (CarLightSource lightSource : lightSources) {

			for (int i = 0; i < 3; ++i) {

				lightPositions.push_back(lightSource.position[i]);
				lightDirections.push_back(lightSource.direction[i]);
				lightColors.push_back(lightSource.color[i]);
			}

			lightAngles.push_back(lightSource.angle);
		}
	}
};