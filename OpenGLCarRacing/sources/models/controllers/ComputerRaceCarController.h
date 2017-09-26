#pragma once

#include "RaceCarController.h"
#include "TerrainLoader.h"

class ComputerRaceCarController : public RaceCarController
{
private:

	bool driveForward();
	bool breakCar();
	int bp;
	TerrainLoader* terrainLoader;
	void turnLeft();
	void turnRight();
	float maxTerrainX;
	float maxTerrainZ;

public:
	ComputerRaceCarController(RaceCar* raceCar, TerrainLoader* terrainLoader);

	virtual void frameUpdate();
	virtual bool isColliding();
};

