#pragma once

#include "glm/vec3.hpp"

#include "RaceCar.h"
#include "TerrainLoader.h"

class RaceCarFactory
{
private:

	static RaceCarFactory* instance;
	RaceCarFactory();

	RaceCar* createRaceCar(string texture);

public:

	static RaceCarFactory* getInstance();

	RaceCar* createPlayerRaceCar();
	RaceCar* createOpponentRaceCar(TerrainLoader* terrainLoader);
};

