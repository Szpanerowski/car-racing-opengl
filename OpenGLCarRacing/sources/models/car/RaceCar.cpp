#include "RaceCar.h"
#include "models/controllers/RaceCarController.h"

#include <cstdio>

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
	printf("Accelerating by x = %f, y = %f, z = %f\n", acceleration.x, acceleration.y, acceleration.z);
}

void RaceCar::frameUpdate() {

	controller->frameUpdate();
	physicalModel->frameUpdate();

	vec3 movementVector = physicalModel->getCurrentMovement();
	carModel->move(movementVector);
}

void RaceCar::render(mat4 view, mat4 projection) {
	carModel->draw(view, projection);
}

vec3 RaceCar::getPosition()
{
	return carModel->getPosition();
}

vec3 RaceCar::getFaceVector()
{
	return physicalModel->getCurrentMovement();
}

void RaceCar::setController(RaceCarController* controller) {
	this->controller = controller;
}

void RaceCar::setModel(Drawable* carModel) {
	this->carModel = carModel;
}