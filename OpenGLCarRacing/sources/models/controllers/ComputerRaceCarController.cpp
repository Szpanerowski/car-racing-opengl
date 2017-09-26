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
	printf("x : %f | z : %f | maxX : %f | maxZ : %f \n", getRaceCar()->getPosition().x, getRaceCar()->getPosition().z, maxTerrainX, maxTerrainZ);
	switch (bp)
	{
	case 0:
		if (getRaceCar()->getPosition().x > (maxTerrainX - 9.0f)) {
			bp++;
		}
		if ((getRaceCar()->getRotationY() < 270 || (getRaceCar()->getPosition().z > 3.0f && getRaceCar()->getPosition().x > 6.0))
			&& getRaceCar()->getPosition().z > 1.0f)
			turnLeft();
		else if (getRaceCar()->getRotationY() > 270 || getRaceCar()->getPosition().z < 1.0f)
			turnRight();
		break;
	case 1:
		if (getRaceCar()->getPosition().z >(maxTerrainZ - 9.0f)) {
			bp++;
		}
		if ((getRaceCar()->getRotationY() < 180 || (getRaceCar()->getPosition().x < (maxTerrainX - 5.0f) && getRaceCar()->getPosition().z > 6.0))
			&& getRaceCar()->getPosition().x < (maxTerrainX - 3.2f))
			turnLeft();
		else if (getRaceCar()->getRotationY() > 180 || getRaceCar()->getPosition().x > (maxTerrainX - 3.2f))
			turnRight();
		break;
	case 2:
		if (getRaceCar()->getPosition().x < 7.0) {
			bp++;
		}
		if ((getRaceCar()->getRotationY() < 90 || (getRaceCar()->getPosition().z < (maxTerrainZ - 5.0f) && getRaceCar()->getPosition().x < (maxTerrainX - 8.0f)))
			&& getRaceCar()->getPosition().z < (maxTerrainZ - 3.2f))
			turnLeft();
		else if (getRaceCar()->getRotationY() > 90 || getRaceCar()->getPosition().z >(maxTerrainZ - 3.2f))
			turnRight();
		break;
	case 3:
		if (getRaceCar()->getPosition().z < 7.0) {
			bp=0;
		}
		if (((getRaceCar()->getRotationY() > 0 && getRaceCar()->getRotationY() < 180) || getRaceCar()->getPosition().x < 1.2f) && getRaceCar()->getPosition().x < 2.8f)
			turnRight();
		else if ((getRaceCar()->getRotationY() > 180 || getRaceCar()->getPosition().x > 2.8f) && getRaceCar()->getPosition().z < (maxTerrainZ - 8.0f))
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