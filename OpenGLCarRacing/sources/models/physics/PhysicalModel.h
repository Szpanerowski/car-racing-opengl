#pragma once

#include "glm/vec3.hpp"

#include "drawing/UpdatedObject.h"
#include "models/physics/PhysicalModelMovement.h"

class PhysicalModel
{
private:

	float mass;
	float interia;

	glm::vec3 currentAcceleration;
	glm::vec3 currentVelocity;
	glm::vec3 currentRotation;
	glm::vec3 nextRotation;

	void correctVelocityVector();

protected:
	
	glm::vec3 getCurrentAcceleration();
	void setCurrentAcceleration(glm::vec3 currentAcceleration);

	glm::vec3 getNextRotation();
	void setNextRotation(glm::vec3 nextRotation);

	glm::vec3 getCurrentVelocity();
	glm::vec3 getCurrentRotation();

public:

	static const glm::vec3 PHYSICAL_MODEL_FORWARD;

	PhysicalModel(float mass, float length, float width);

	virtual void applyForce(glm::vec3 forceVector, glm::vec3 pivotShift);
	virtual PhysicalModelMovement updatePhysics(float deltaSeconds);

	float getMass();
};

