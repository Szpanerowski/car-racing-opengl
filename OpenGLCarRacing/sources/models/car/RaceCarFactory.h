#pragma once

#include "glm/vec3.hpp"

#include "RaceCar.h"

class RaceCarFactory
{
private:

	static RaceCarFactory* instance;
	RaceCarFactory();

	RaceCar* createRaceCar(glm::vec3 position);

public:

	static RaceCarFactory* getInstance();

	RaceCar* createPlayerRaceCar(glm::vec3 position);
	RaceCar* createOpponentRaceCar(glm::vec3 position);
};

