#pragma once

#include "glm/vec3.hpp"

#include "RaceCar.h"

class RaceCarFactory
{
private:

	static RaceCarFactory* instance;
	RaceCarFactory();

	RaceCar* createRaceCar();

public:

	static RaceCarFactory* getInstance();

	RaceCar* createPlayerRaceCar();
	RaceCar* createOpponentRaceCar();
};

