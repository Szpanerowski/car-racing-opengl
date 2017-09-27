#include "ComputerRaceCarController.h"
#include "models/car/RaceCar.h"

using namespace glm;

ComputerRaceCarController::ComputerRaceCarController(RaceCar* raceCar, TerrainLoader* terrainLoader)
	: RaceCarController(raceCar) {
	ComputerRaceCarController::terrainLoader = terrainLoader;
	bp = 0;
	maxTerrainX = terrainLoader->getX();
	maxTerrainZ = terrainLoader->getZ();
}

void ComputerRaceCarController::frameUpdate() {
	switch (bp)
	{
	case 0:
		if (getRaceCar()->getPosition().x > (maxTerrainX - 9.0f)) {
			bp++;
			break;
		}
		if (((getRaceCar()->getRotationY() < 270 && getRaceCar()->getRotationY() > 100) || getRaceCar()->getPosition().z > 3.5f)
			&& getRaceCar()->getPosition().x > 4.0f)
			turnLeft();
		else if (getRaceCar()->getRotationY() > 270 || getRaceCar()->getRotationY() < 100 || getRaceCar()->getPosition().z < 1.5f)
			turnRight();
		break;
	case 1:
		if (getRaceCar()->getPosition().z >(maxTerrainZ - 9.0f)) {
			bp++;
			break;
		}
		if ((getRaceCar()->getRotationY() < 180 || getRaceCar()->getPosition().x < (maxTerrainX - 5.0f))
			&& getRaceCar()->getPosition().z > (4.0f))
			turnLeft();
		else if (getRaceCar()->getRotationY() > 180 || getRaceCar()->getPosition().x > (maxTerrainX - 3.2f))
			turnRight();
		break;
	case 2:
		if (getRaceCar()->getPosition().x < 8.0f) {
			bp++;
			break;
		}
		if ((getRaceCar()->getRotationY() < 90 || getRaceCar()->getPosition().z < (maxTerrainZ - 5.0f))
			&& getRaceCar()->getPosition().x < (maxTerrainX - 5.0f))
			turnLeft();
		else if (getRaceCar()->getRotationY() > 90 || getRaceCar()->getPosition().z >(maxTerrainZ - 3.2f))
			turnRight();
		break;
	case 3:
		if (getRaceCar()->getPosition().z < 8.0f) {
			bp=0;
			break;
		}
		if (((getRaceCar()->getRotationY() > 0 && getRaceCar()->getRotationY() < 180) || getRaceCar()->getPosition().z < 1.5f))
			turnRight();
		else if ((getRaceCar()->getRotationY() > 180 || getRaceCar()->getPosition().x > 3.0f) && getRaceCar()->getPosition().z < (maxTerrainZ - 6.0f))
			turnLeft();
		break;
	}


	if (driveForward())
		getRaceCar()->accelerate(1);
	else if (breakCar())
	{
		if (getRaceCar()->getPhysicalModel().getCurrentVelocity().z > 0.03)
		getRaceCar()->accelerate(-1);
	}

	
}

bool ComputerRaceCarController::isColliding()
{
	return false;
}

bool ComputerRaceCarController::driveForward() {
	vec3 helperVec = getRaceCar()->getPosition() + getRaceCar()->getForwardVector()*8.0f;
	if (ComputerRaceCarController::terrainLoader->getTerrainType(helperVec.x, helperVec.z) == TerrainLoader::Road)
	{
		return true;
	}
	else
		return false;
}

bool ComputerRaceCarController::breakCar() {
	vec3 helperVec = getRaceCar()->getPosition() + getRaceCar()->getForwardVector()*8.0f;
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