#pragma once

#include "glm/vec3.hpp"
#include "drawing/UpdatedObject.h"

class PhysicalModel
{
private:

	float mass;

	glm::vec3 currentAcceleration;
	glm::vec3 currentMovement;
	glm::vec3 currentRotation;
	glm::vec3 nextRotation;

protected:
	
	glm::vec3 getCurrentAcceleration();
	void setCurrentAcceleration(glm::vec3 currentAcceleration);

	glm::vec3 getNextRotation();
	void setNextRotation(glm::vec3 nextRotation);

public:

	PhysicalModel(float mass);

	virtual void applyForce(glm::vec3 forceVector, glm::vec3 pivotShift);
	virtual void updatePhysics();

	glm::vec3 getCurrentMovement();
	glm::vec3 getCurrentRotation();
};

