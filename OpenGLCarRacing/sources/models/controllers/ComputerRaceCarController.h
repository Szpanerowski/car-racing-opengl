#pragma once

#include "RaceCarController.h"
#include "TerrainLoader.h"

class ComputerRaceCarController : public RaceCarController
{
private:

	bool driveForward();
	bool driveBackward();
	bool turnLeft();
	bool turnRight();
	TerrainLoader* terrainLoader;

public:
	ComputerRaceCarController(RaceCar* raceCar, TerrainLoader* terrainLoader);

	virtual void frameUpdate();
};

