#include "PlayerRaceCarController.h"
#include "RaceCarController.h"
#include "input/InputHandler.h"

#include "gl/freeglut.h"
#include "glm/vec3.hpp"

using namespace glm;

PlayerRaceCarController::PlayerRaceCarController(RaceCar* raceCar)
	: RaceCarController(raceCar) {
}

void PlayerRaceCarController::frameUpdate() {

	RaceCar* playerCar = getRaceCar();
	
	if (turnLeft())
		playerCar->turn(1);
	else if (turnRight())
		playerCar->turn(-1);
	else playerCar->turn(0);

	if (driveForward())
		playerCar->accelerate(1);
	else if (driveBackward())
		playerCar->accelerate(-1);
}

bool PlayerRaceCarController::driveForward() {

	bool forward = InputHandler::getInstance()->checkSpecialKey(GLUT_KEY_UP);
	bool backward = InputHandler::getInstance()->checkSpecialKey(GLUT_KEY_DOWN);

	return checkOppositeValues(forward, backward);
}

bool PlayerRaceCarController::driveBackward() {
	
	bool forward = InputHandler::getInstance()->checkSpecialKey(GLUT_KEY_UP);
	bool backward = InputHandler::getInstance()->checkSpecialKey(GLUT_KEY_DOWN);

	return checkOppositeValues(backward, forward);
}

bool PlayerRaceCarController::turnLeft() {
	
	bool left = InputHandler::getInstance()->checkSpecialKey(GLUT_KEY_LEFT);
	bool right = InputHandler::getInstance()->checkSpecialKey(GLUT_KEY_RIGHT);

	return checkOppositeValues(left, right);
}

bool PlayerRaceCarController::turnRight() {

	bool left = InputHandler::getInstance()->checkSpecialKey(GLUT_KEY_LEFT);
	bool right = InputHandler::getInstance()->checkSpecialKey(GLUT_KEY_RIGHT);

	return checkOppositeValues(right, left);
}

bool PlayerRaceCarController::checkOppositeValues(bool primary, bool opposite) {

	if (primary && opposite)
		return false;

	return primary;
}