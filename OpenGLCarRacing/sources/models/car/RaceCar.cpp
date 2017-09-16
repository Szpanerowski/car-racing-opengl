#include "RaceCar.h"
#include "models/controllers/RaceCarController.h"

#include <cstdio>

using namespace glm;

RaceCar::RaceCar(Drawable* carModel, PhysicalModel* physicalModel) {
	
	this->carModel = carModel;
	this->physicalModel = physicalModel;
}

void RaceCar::accelerate(float acceleration) {

	physicalModel->applyForce(getForwardVector() * acceleration, vec3(0, 0, 0));
}

void RaceCar::brake(float braking) {

	physicalModel->applyForce(getForwardVector() * -braking, vec3(0, 0, 0));
}

void RaceCar::turn(float turnLeftDirection) {

	vec3 forwardVector = getForwardVector();
	physicalModel->applyForce(getForwardVector(), vec3(0, 1, 0) * turnLeftDirection);
}

void RaceCar::frameUpdate() {

	controller->frameUpdate();
	physicalModel->updatePhysics();

	vec3 movementVector = physicalModel->getCurrentMovement();
	carModel->move(movementVector);

	vec3 rotationVector = physicalModel->getCurrentRotation();

	carModel->rotate(rotationVector);
}

void RaceCar::render(mat4 view, mat4 projection) {
	carModel->draw(view, projection);
}

vec3 RaceCar::getPosition()
{
	return carModel->getPosition();
}

vec3 RaceCar::getForwardVector()
{
	return carModel->getForwardVector();
}

void RaceCar::setController(RaceCarController* controller) {
	this->controller = controller;
}