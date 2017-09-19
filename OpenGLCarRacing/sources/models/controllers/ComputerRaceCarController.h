#pragma once

#include "RaceCarController.h"
#include "TerrainLoader.h"

class ComputerRaceCarController : public RaceCarController
{
private:

	bool driveForward();
	bool breakCar();
	bool turnLeft();
	bool turnRight();
	int bp;
	TerrainLoader* terrainLoader;

public:
	ComputerRaceCarController(RaceCar* raceCar, TerrainLoader* terrainLoader);

	virtual void frameUpdate();
	virtual bool isColliding();
};

