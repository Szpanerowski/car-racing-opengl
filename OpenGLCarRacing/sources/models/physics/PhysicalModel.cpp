#include "PhysicalModel.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

const vec3 PhysicalModel::PHYSICAL_MODEL_FORWARD = vec3(0, 0, 1);

PhysicalModel::PhysicalModel(float mass, float length, float width) {

	this->mass = mass;
	this->interia = mass * (length * length + width * width) / 12.0f;

	currentAcceleration = vec3(0, 0, 0);
	currentVelocity = vec3(0, 0, 0);
	currentRotation = vec3(0, 0, 0);
	nextRotation = vec3(0, 0, 0);
}

void PhysicalModel::applyForce(vec3 forceVector, vec3 pivotShift) {

	currentAcceleration += forceVector / mass;

	vec3 crossProduct = cross(pivotShift, forceVector);
	float momentum = length(crossProduct) * sign(crossProduct.y);

	nextRotation.y += degrees(momentum / interia);
}

PhysicalModelMovement PhysicalModel::updatePhysics(float deltaSeconds) {

	currentVelocity += currentAcceleration * deltaSeconds;
	currentAcceleration = vec3(0, 0, 0);

	currentRotation = nextRotation;
	nextRotation = vec3(0, 0, 0);

	PhysicalModelMovement resultMovement = PhysicalModelMovement(currentVelocity, currentRotation);

	correctVelocityVector();

	return resultMovement;
}

void PhysicalModel::correctVelocityVector() {

	currentVelocity = rotate(mat4(1.0f), radians(-currentRotation.y), vec3(0, 1, 0)) * vec4(currentVelocity, 0);
}

vec3 PhysicalModel::getCurrentVelocity() {
	return this->currentVelocity;
}

vec3 PhysicalModel::getCurrentRotation() {
	return this->currentRotation;
}

void PhysicalModel::setCurrentMovement(glm::vec3 currentMovement) {
	this->currentVelocity = currentMovement;
}

void PhysicalModel::stopMovement() {
	this->currentVelocity = vec3(0, 0, 0);
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

float PhysicalModel::getMass() {
	return this->mass;
}