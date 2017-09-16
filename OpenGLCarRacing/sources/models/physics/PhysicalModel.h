#pragma once

#include "glm/vec3.hpp"
#include "drawing/UpdatedObject.h"

class PhysicalModel
{
private:
	glm::vec3 currentAcceleration;
	glm::vec3 currentMovement;
	glm::vec3 currentRotation;
	glm::vec3 nextRotation;

public:

	PhysicalModel();

	virtual void applyForce(glm::vec3 forceVector, glm::vec3 pivotShift);
	
	void updatePhysics();

	glm::vec3 getCurrentMovement();
	glm::vec3 getCurrentRotation();
};

