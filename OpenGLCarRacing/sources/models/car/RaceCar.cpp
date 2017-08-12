#include "RaceCar.h"
#include "models/controllers/RaceCarController.h"

using namespace glm;

RaceCar::RaceCar() {

	this->position = vec3(0, 0, 0);
}

RaceCar::RaceCar(vec3 position)
	: RaceCar() {

	this->position = position;
}

RaceCar::RaceCar(vec3 position, PhysicalModel* physicalModel)
	: RaceCar(position) {
	
	this->physicalModel = physicalModel;
}

void RaceCar::accelerate(vec3 acceleration) {

	physicalModel->applyForce(acceleration, vec3(0, 0, 0));
}

void RaceCar::frameUpdate() {

	controller->frameUpdate();

	vec3 movementVector = physicalModel->getCurrentMovement();
}

void RaceCar::render() {
}

void RaceCar::setController(RaceCarController* controller) {
	this->controller = controller;
}