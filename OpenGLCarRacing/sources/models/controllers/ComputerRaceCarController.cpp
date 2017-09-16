#include "ComputerRaceCarController.h"
#include "models/car/RaceCar.h"

using namespace glm;

ComputerRaceCarController::ComputerRaceCarController(RaceCar* raceCar, TerrainLoader* terrainLoader)
	: RaceCarController(raceCar) {
	ComputerRaceCarController::terrainLoader = terrainLoader;
}

void ComputerRaceCarController::frameUpdate() {

	if (driveForward())
		getRaceCar()->accelerate(vec3(0, 0, 0.001f));
	else
		getRaceCar()->accelerate(vec3(0, 0, -0.001f));
}

bool ComputerRaceCarController::driveForward() {
	if (ComputerRaceCarController::terrainLoader->getTerrainType(getRaceCar()->getPosition().x, getRaceCar()->getPosition().z + 3) == TerrainLoader::Road)
		return true;
	else
		return false;
}

bool ComputerRaceCarController::driveBackward() {
	return false;
}

bool ComputerRaceCarController::turnLeft() {
	return false;
}

bool ComputerRaceCarController::turnRight() {
	return false;
}