#pragma once

#include "models/physics/PhysicalModel.h"
#include "models/car/RaceCar.h"

class RaceCar;

class RaceCarPhysicalModel : public PhysicalModel {

private:

	RaceCar* raceCar;

	glm::vec3 calculateAerodynamicDrag();
	glm::vec3 calculateRollingResistance();

	static const float AERODYNAMIC_DRAG_CONST;
	static const float ROLLING_RESISTANCE_CONST;
	static const float SIDE_RESISTANCE_CONST;
	static const float GRAVITY_ACCELERATION;

	void applyLateralForces(float deltaSeconds);
	glm::vec3 getSideFriction(float deltaSeconds);

public:

	RaceCarPhysicalModel(RaceCar* raceCar, float mass, float length, float width);

	virtual PhysicalModelMovement updatePhysics(float deltaSeconds);
};