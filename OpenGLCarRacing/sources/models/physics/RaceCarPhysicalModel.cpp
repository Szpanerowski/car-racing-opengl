#include "RaceCarPhysicalModel.h"

#include "glm/glm.hpp"

using namespace glm;
using namespace std;

const float RaceCarPhysicalModel::AERODYNAMIC_DRAG_CONST = 0.7;
const float RaceCarPhysicalModel::ROLLING_RESISTANCE_CONST = 0.04;
const float RaceCarPhysicalModel::SIDE_RESISTANCE_CONST = 0.1;
const float RaceCarPhysicalModel::GRAVITY_ACCELERATION = 9.81;

RaceCarPhysicalModel::RaceCarPhysicalModel(RaceCar* raceCar, float mass, float length, float width)
	: PhysicalModel(mass, length, width) {

	this->raceCar = raceCar;
}

PhysicalModelMovement RaceCarPhysicalModel::updatePhysics(float deltaSeconds) {
	
	vec3 resistanceVector = calculateAerodynamicDrag() + calculateRollingResistance();

	applyForce(resistanceVector * getMass(), vec3(0, 0, 0));
	applyLateralForces(deltaSeconds);

	return PhysicalModel::updatePhysics(deltaSeconds);
}

void RaceCarPhysicalModel::applyLateralForces(float deltaSeconds) {

	vec3 sideFriction = getSideFriction(deltaSeconds);
	applyForce(sideFriction, vec3(0, 0, 0));

	/*float zVelocity = getCurrentVelocity().z;

	float frontRearWheelsDistance = length(raceCar->getFrontWheelsShift() - raceCar->getRearWheelsShift());
	float corneringAngle = raceCar->getLeftTurnDegrees();
	float corneringRadius = frontRearWheelsDistance / sin(radians(corneringAngle));
	float direction = sign(raceCar->getLeftTurnDegrees());

	vec3 corneringVector = rotate(mat4(1.0f), radians(corneringAngle), vec3(0, 1, 0)) * vec4(0, 0, 1, 0);
	vec3 pCorneringVector = vec3(corneringVector.z, 0, -corneringVector.x) * direction * sign(zVelocity);

	applyForce(pCorneringVector * zVelocity * zVelocity / corneringRadius, vec3(0, 0, 1));*/

	float corneringAngle = raceCar->getLeftTurnDegrees();
	float forwardMovement = sign(getCurrentVelocity().z);

	const float corneringConst = 25;
	float corneringForce = length(PHYSICAL_MODEL_FORWARD) * tan(radians(corneringAngle)) * corneringConst;

	applyForce(vec3(corneringForce, 0, 0), forwardMovement * raceCar->getFrontWheelsShift());
}

vec3 RaceCarPhysicalModel::getSideFriction(float deltaSeconds) {

	const int wheelsCount = 4;
	float xVelocity = getCurrentVelocity().x;

	float sideResistance = -sign(xVelocity) * wheelsCount * SIDE_RESISTANCE_CONST * GRAVITY_ACCELERATION * getMass();
	float resultResistance = std::min(abs(sideResistance), abs(xVelocity) * getMass() / deltaSeconds) * sign(sideResistance);

	return vec3(resultResistance, 0, 0);
}

vec3 RaceCarPhysicalModel::calculateAerodynamicDrag() {
	return -AERODYNAMIC_DRAG_CONST * getCurrentVelocity() * length(getCurrentVelocity());
}

vec3 RaceCarPhysicalModel::calculateRollingResistance() {
	return -ROLLING_RESISTANCE_CONST * getCurrentVelocity();
}
