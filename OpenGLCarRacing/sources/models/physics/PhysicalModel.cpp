#include "PhysicalModel.h"

#include "glm/glm.hpp"

using namespace glm;

PhysicalModel::PhysicalModel() {

	currentAcceleration = vec3(0, 0, 0);
	currentMovement = vec3(0, 0, 0);
}

void PhysicalModel::applyForce(vec3 forceVector, vec3 pivotShift) {

	currentAcceleration = forceVector;
}

void PhysicalModel::frameUpdate() {

	if (length(currentMovement) < 0.1f && currentAcceleration == vec3(0, 0, 0))
		currentMovement = vec3(0, 0, 0);
	else {

		currentMovement += currentAcceleration * 0.95f;
	}
	
	currentAcceleration = -0.01f * currentMovement;
}

vec3 PhysicalModel::getCurrentMovement() {
	return this->currentMovement;
}

Rotation PhysicalModel::getCurrentRotation() {
	return this->currentRotation;
}