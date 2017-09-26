#include "ComputerRaceCarController.h"
#include "models/car/RaceCar.h"

using namespace glm;

ComputerRaceCarController::ComputerRaceCarController(RaceCar* raceCar, TerrainLoader* terrainLoader)
	: RaceCarController(raceCar) {
	ComputerRaceCarController::terrainLoader = terrainLoader;
	bp = 0;
}

void ComputerRaceCarController::frameUpdate() {
	switch (bp)
	{
	case 0:
		if (getRaceCar()->getPosition().x > 24.5) {
			bp++;
		}
		if (getRaceCar()->getRotationY() < 270)
			turnLeft();
		else if (getRaceCar()->getRotationY() > 270)
			turnRight();
		break;
	case 1:
		if (getRaceCar()->getPosition().z > 24.5) {
			bp++;
		}
		if (getRaceCar()->getRotationY() < 180)
			turnLeft();
		else if (getRaceCar()->getRotationY() > 180)
			turnRight();
		break;
	case 2:
		if (getRaceCar()->getPosition().x < 4.5) {
			bp++;
		}
		if (getRaceCar()->getRotationY() < 90)
			turnLeft();
		else if (getRaceCar()->getRotationY() > 90)
			turnRight();
		break;
	case 3:
		if (getRaceCar()->getPosition().z < 4.5) {
			bp=0;
		}
		if (getRaceCar()->getRotationY() > 0 && getRaceCar()->getRotationY() < 180)
			turnRight();
		else if (getRaceCar()->getRotationY() > 180)
			turnLeft();
		break;
	}


	if (driveForward())
		getRaceCar()->accelerate(1);
	else if (breakCar())
	{
		if (getRaceCar()->getPhysicalModel().getCurrentVelocity().z > 0.02)
		getRaceCar()->accelerate(-1);
	}

	
}

bool ComputerRaceCarController::isColliding()
{
	return false;
}

bool ComputerRaceCarController::driveForward() {
	vec3 helperVec = getRaceCar()->getPosition() + getRaceCar()->getForwardVector()*7.0f;
	if (ComputerRaceCarController::terrainLoader->getTerrainType(helperVec.x, helperVec.z) == TerrainLoader::Road)
	{
		return true;
	}
	else
		return false;
}

bool ComputerRaceCarController::breakCar() {
	vec3 helperVec = getRaceCar()->getPosition() + getRaceCar()->getForwardVector()*7.0f;
	if (ComputerRaceCarController::terrainLoader->getTerrainType(helperVec.x, helperVec.z) != TerrainLoader::Road)
	{
		return true;	
	}
	else
		return false;
}

void ComputerRaceCarController::turnLeft() {
	if (getRaceCar()->getPhysicalModel().getCurrentVelocity().z>0)
		getRaceCar()->turn(1);
	else if (getRaceCar()->getPhysicalModel().getCurrentVelocity().z<0)
		getRaceCar()->turn(-1);
}

void ComputerRaceCarController::turnRight() {
	if (getRaceCar()->getPhysicalModel().getCurrentVelocity().z>0)
		getRaceCar()->turn(-1);
	else if (getRaceCar()->getPhysicalModel().getCurrentVelocity().z<0)
		getRaceCar()->turn(1);
}