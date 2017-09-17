#include "PhysicalModel.h"

#include "glm/glm.hpp"

using namespace glm;

PhysicalModel::PhysicalModel() {

	currentAcceleration = vec3(0, 0, 0);
	currentMovement = vec3(0, 0, 0);
	currentRotation = vec3(0, 0, 0);
	nextRotation = vec3(0, 0, 0);
}

void PhysicalModel::applyForce(vec3 forceVector, vec3 pivotShift) {

	if (pivotShift == vec3(0, 0, 0)) {

		currentAcceleration = forceVector;
	}
	else {

		pivotShift *= glm::length(forceVector);

		vec3 rotation = vec3(degrees((pivotShift.x)), degrees(asin(pivotShift.y)), degrees(asin(pivotShift.z)));
		nextRotation += rotation;
	}
}

void PhysicalModel::updatePhysics() {

	if (length(currentMovement) < 1 && currentAcceleration == vec3(0, 0, 0))
		currentMovement = vec3(0, 0, 0);
	else {

		//temp
		for (int i = 0;i < 3;i++)
		{
			if (currentMovement[i] > 0)
				currentMovement[i] -= 0.008f;
			else if (currentMovement[i] < 0)
				currentMovement[i] += 0.008f;
		}
		currentMovement += currentAcceleration * 0.95f;
		//end temp

	}
	
	currentAcceleration = -0.01f * currentMovement;

	currentRotation = nextRotation;
	nextRotation = vec3(0, 0, 0);
}

vec3 PhysicalModel::getCurrentMovement() {
	return this->currentMovement;
}

vec3 PhysicalModel::getCurrentRotation() {
	return this->currentRotation;
}