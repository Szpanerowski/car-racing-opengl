#pragma once

#include "models/physics/PhysicalModel.h"
#include "models/car/RaceCar.h"

class RaceCar;

class RaceCarPhysicalModel : public PhysicalModel {

private:

	RaceCar* raceCar;

	glm::vec3 calculateEngineForce(float acceleration);
	glm::vec3 calculateAerodynamicDrag();
	glm::vec3 calculateRollingResistance();

	static const float AERODYNAMIC_DRAG_CONST;
	static const float ROLLING_RESISTANCE_CONST;

	void applyTurnRotation();

public:

	RaceCarPhysicalModel(RaceCar* raceCar, float mass);

	void updatePhysics();
	void applyAcceleration(float acceleration);
};