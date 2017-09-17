#include "RaceCar.h"
#include "models/controllers/RaceCarController.h"

#include <cstdio>

#include "glm/gtx/vector_angle.hpp"

using namespace glm;

RaceCar::RaceCar(Drawable* carModel) {
	
	this->carModel = carModel;
	this->turnVector = carModel->getForwardVector();
	this->frontWheelsShift = vec3(0, 0, 0.5);
}

void RaceCar::accelerate(float acceleration) {

	physicalModel->applyAcceleration(acceleration);
}

void RaceCar::turn(float turnLeftDirection) {

	this->turnVector = vec3(turnLeftDirection, 0, 0);
}

void RaceCar::frameUpdate() {

	controller->frameUpdate();
	physicalModel->updatePhysics();

	vec3 movementVector = physicalModel->getCurrentMovement();
	vec3 velocityVector = rotatePhysicalModelVector(movementVector);
	carModel->move(velocityVector);

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

vec3 RaceCar::getTurnVector() {
	return this->turnVector;
}

void RaceCar::setController(RaceCarController* controller) {
	this->controller = controller;
}

void RaceCar::setPhysicalModel(RaceCarPhysicalModel* physicalModel) {
	this->physicalModel = physicalModel;
}

vec3 RaceCar::getFrontWheelsShift() {
	return this->frontWheelsShift;
}

vec3 RaceCar::rotatePhysicalModelVector(vec3 vector) {

	vec3 physicalModelVector = vec3(0, 0, 1);
	vec3 forward = normalize(carModel->getForwardVector());
	float rotationAngle = angle(physicalModelVector, forward);
	float rotationDegrees = degrees(rotationAngle);
	
	vec3 result = rotate(mat4(1.0f), rotationAngle, vec3(0, 1, 0)) * vec4(vector, 0);

	return result;
}