#pragma once

#include "glm/vec3.hpp"
#include "models/physics/Rotation.h"
#include "drawing/FrameUpdateableObject.h"

class PhysicalModel : public FrameUpdateableObject
{
private:
	glm::vec3 currentAcceleration;
	glm::vec3 currentMovement;
	Rotation rotationSpeed;
	Rotation currentRotation;

public:

	PhysicalModel();

	virtual void applyForce(glm::vec3 forceVector, glm::vec3 pivotShift);
	virtual void frameUpdate();

	glm::vec3 getCurrentMovement();
	Rotation getCurrentRotation();
};

