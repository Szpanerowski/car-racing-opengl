#include "ComputerRaceCarController.h"
#include "models/car/RaceCar.h"

using namespace glm;

ComputerRaceCarController::ComputerRaceCarController(RaceCar* raceCar, TerrainLoader* terrainLoader)
	: RaceCarController(raceCar) {
	ComputerRaceCarController::terrainLoader = terrainLoader;
	bp = 0;
}

void ComputerRaceCarController::frameUpdate() {

	if (driveForward())
		getRaceCar()->accelerate(0.01);
	else if (breakCar())
	{
		getRaceCar()->brake(0.01);
		bp += 2;
		if (bp >= 8)
			bp = bp % 8;
		getRaceCar()->turn(-0.1);
	}
}

bool ComputerRaceCarController::driveForward() {
	vec3 helperVec = getRaceCar()->getPosition() + getRaceCar()->getForwardVector()*3.0f;
	if (ComputerRaceCarController::terrainLoader->getTerrainType(helperVec.x, helperVec.z) == TerrainLoader::Road)
		return true;
	else
		return false;
}

bool ComputerRaceCarController::breakCar() {
	vec3 helperVec = getRaceCar()->getPosition() + getRaceCar()->getForwardVector()*3.0f;
	if (ComputerRaceCarController::terrainLoader->getTerrainType(helperVec.x, helperVec.z) != TerrainLoader::Road)
		return true;
	else
		return false;
}

bool ComputerRaceCarController::turnLeft() {
	return false;
}

bool ComputerRaceCarController::turnRight() {
	return false;
}