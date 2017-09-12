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

	if (driveForward())
		getRaceCar()->accelerate(vec3(0, 0, 0.001f));
	else if (driveBackward())
		getRaceCar()->accelerate(vec3(0, 0, -0.001f));
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