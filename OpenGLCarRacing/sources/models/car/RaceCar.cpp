#include "RaceCar.h"
#include "models/controllers/RaceCarController.h"

#include "glm/gtx/vector_angle.hpp"

#include <cstdio>

using namespace glm;

RaceCar::RaceCar(Drawable* carModel) {
	
	this->carModel = carModel;
	this->frontWheelsShift = vec3(0, 0, 1);
	this->rearWheelsShift = vec3(0, 0, -1);
	this->leftTurnDegrees = 0;
	this->maxTurnDegrees = 45;
	this->engineMaxForce = 150;
}

void RaceCar::accelerate(float acceleration) {

	physicalModel->applyForce(vec3(0, 0, acceleration * engineMaxForce), vec3(0, 0, 0));
}

void RaceCar::turn(float leftTurnDirection) {
	this->leftTurnDegrees = leftTurnDirection * maxTurnDegrees;
}

void RaceCar::frameUpdate(float deltaSeconds) {

	controller->frameUpdate();
	PhysicalModelMovement modelMovement = physicalModel->updatePhysics(deltaSeconds);

	vec3 velocityVector = modelMovement.velocity;
	vec3 rotatedVelocityVector = rotatePhysicalModelVector(velocityVector);
	carModel->move(rotatedVelocityVector);

	vec3 rotationVector = modelMovement.rotation;
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

void RaceCar::setPosition(vec3 position) {
	carModel->setPosition(position);
}

void RaceCar::setRotation(vec3 rotation) {
	carModel->setRotation(rotation);
}

float RaceCar::getLeftTurnDegrees() {
	return this->leftTurnDegrees;
}

vec3 RaceCar::getFrontWheelsShift() {
	return this->frontWheelsShift;
}

vec3 RaceCar::getRearWheelsShift() {
	return this->rearWheelsShift;
}

void RaceCar::setController(RaceCarController* controller) {
	this->controller = controller;
}

void RaceCar::setPhysicalModel(RaceCarPhysicalModel* physicalModel) {
	this->physicalModel = physicalModel;
}

vec3 RaceCar::rotatePhysicalModelVector(vec3 vector) {

	vec3 physicalModelVector = PhysicalModel::PHYSICAL_MODEL_FORWARD;
	vec3 forward = carModel->getForwardVector();

	vec2 firstVector = normalize(vec2(physicalModelVector.z, physicalModelVector.x));
	vec2 secondVector = normalize(vec2(forward.z, forward.x));

	float rotationAngle = orientedAngle(firstVector, secondVector);
	vec3 result = rotate(mat4(1.0f), rotationAngle, vec3(0, 1, 0)) * vec4(vector, 0);

	return result;
}