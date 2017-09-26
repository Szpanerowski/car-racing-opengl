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
		getRaceCar()->accelerate(1);
	else if (breakCar())
	{
		getRaceCar()->accelerate(-1);
		bp += 2;
		if (bp >= 8)
			bp = bp % 8;
		if(getRaceCar()->getPhysicalModel().getCurrentVelocity().z>0)
			getRaceCar()->turn(-1);
		else if (getRaceCar()->getPhysicalModel().getCurrentVelocity().z<0)
			getRaceCar()->turn(1);
	}

	
}

bool ComputerRaceCarController::isColliding()
{
	return false;
}

bool ComputerRaceCarController::driveForward() {
	vec3 helperVec = getRaceCar()->getPosition() + getRaceCar()->getForwardVector()*6.0f;
	if (ComputerRaceCarController::terrainLoader->getTerrainType(helperVec.x-1, helperVec.z) == TerrainLoader::Road)
	{
		printf("ROAD x : %f | z : %f \n", helperVec.x, helperVec.z);
		return true;
	}
	else
		return false;
}

bool ComputerRaceCarController::breakCar() {
	vec3 helperVec = getRaceCar()->getPosition() + getRaceCar()->getForwardVector()*6.0f;
	if (ComputerRaceCarController::terrainLoader->getTerrainType(helperVec.x-1, helperVec.z) != TerrainLoader::Road)
	{
		printf("GRASS x : %f | z : %f \n", helperVec.x, helperVec.z);
		return true;	
	}
	else
		return false;
}

bool ComputerRaceCarController::turnLeft() {
	return false;
}

bool ComputerRaceCarController::turnRight() {
	return false;
}