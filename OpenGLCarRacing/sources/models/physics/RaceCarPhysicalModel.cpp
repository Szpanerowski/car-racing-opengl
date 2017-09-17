#include "RaceCarPhysicalModel.h"

#include "glm/glm.hpp"

using namespace glm;

const float RaceCarPhysicalModel::AERODYNAMIC_DRAG_CONST = 0.05;
const float RaceCarPhysicalModel::ROLLING_RESISTANCE_CONST = 0.03;

RaceCarPhysicalModel::RaceCarPhysicalModel(RaceCar* raceCar, float mass)
	: PhysicalModel(mass) {

	this->raceCar = raceCar;
}

void RaceCarPhysicalModel::updatePhysics() {
	
	vec3 acceleration = getCurrentAcceleration();
	
	acceleration = acceleration - calculateAerodynamicDrag() - calculateRollingResistance();
	setCurrentAcceleration(acceleration);

	applyTurnRotation();

	PhysicalModel::updatePhysics();
}

void RaceCarPhysicalModel::applyTurnRotation() {

	PhysicalModel::applyForce(raceCar->getTurnVector(), raceCar->getFrontWheelsShift());
}

void RaceCarPhysicalModel::applyAcceleration(float acceleration) {

	PhysicalModel::applyForce(calculateEngineForce(acceleration), vec3(0, 0, 0));
}

vec3 RaceCarPhysicalModel::calculateEngineForce(float acceleration) {
	return vec3(0, 0, acceleration);
}

vec3 RaceCarPhysicalModel::calculateAerodynamicDrag() {
	return AERODYNAMIC_DRAG_CONST * getCurrentMovement() * length(getCurrentMovement());
}

vec3 RaceCarPhysicalModel::calculateRollingResistance() {
	return ROLLING_RESISTANCE_CONST * getCurrentMovement();
}
