#include "PhysicalModel.h"

#include "glm/glm.hpp"

using namespace glm;

PhysicalModel::PhysicalModel(float mass) {

	this->mass = mass;

	currentAcceleration = vec3(0, 0, 0);
	currentMovement = vec3(0, 0, 0);
	currentRotation = vec3(0, 0, 0);
	nextRotation = vec3(0, 0, 0);
}

void PhysicalModel::applyForce(vec3 forceVector, vec3 pivotShift) {

	currentAcceleration += vec3(0, 0, dot(forceVector, vec3(0, 0, 1)));

	const float i = 1;
	float m = length(cross(pivotShift, forceVector));

	nextRotation.y += m / i;
}

void PhysicalModel::updatePhysics() {

	currentMovement += currentAcceleration;
	currentAcceleration = vec3(0, 0, 0);

	currentRotation = nextRotation;
	nextRotation = vec3(0, 0, 0);
}

vec3 PhysicalModel::getCurrentMovement() {
	return this->currentMovement;
}

vec3 PhysicalModel::getCurrentRotation() {
	return this->currentRotation;
}

vec3 PhysicalModel::getCurrentAcceleration() {
	return this->currentAcceleration;
}

void PhysicalModel::setCurrentAcceleration(glm::vec3 currentAcceleration) {
	this->currentAcceleration = currentAcceleration;
}

vec3 PhysicalModel::getNextRotation() {
	return this->nextRotation;
}

void PhysicalModel::setNextRotation(glm::vec3 nextRotation) {
	this->nextRotation = nextRotation;
}