#include "RaceCar.h"
#include "models/controllers/RaceCarController.h"
#include "models/physics/PhysicalModelMovement.h"

#include "glm/gtx/vector_angle.hpp"

#include "glm/gtx/vector_angle.hpp"

#include <cstdio>

using namespace glm;

RaceCar::RaceCar(Drawable* carModel) {
	
	this->carModel = carModel;
	this->frontWheelsShift = vec3(0, 0, 1);
	this->rearWheelsShift = vec3(0, 0, -1);
	this->leftTurnDegrees = 0;
	this->maxTurnDegrees = 45;
	this->engineMaxForce = 150;
}

void RaceCar::accelerate(float acceleration) {

	physicalModel->applyForce(vec3(0, 0, acceleration * engineMaxForce), vec3(0, 0, 0));

	if (acceleration * physicalModel->getCurrentVelocity().z < 0)
		physicalModel->applyForce(vec3(0, 0, acceleration * (engineMaxForce*3)), vec3(0, 0, 0));
	else
		physicalModel->applyForce(vec3(0, 0, acceleration * engineMaxForce), vec3(0, 0, 0));
}

void RaceCar::turn(float leftTurnDirection) {
	this->leftTurnDegrees = leftTurnDirection * maxTurnDegrees;
}

void RaceCar::frameUpdate(float deltaSeconds) {

	controller->frameUpdate();
	PhysicalModelMovement modelMovement = physicalModel->updatePhysics(deltaSeconds);

	//collisions
	updateColliderPosition();
	if (isColliding()) {
		//afterCollision();
	}

	vec3 velocityVector = modelMovement.velocity;
	vec3 rotatedVelocityVector = rotatePhysicalModelVector(velocityVector);
	carModel->move(rotatedVelocityVector);

	vec3 rotationVector = modelMovement.rotation;
	carModel->rotate(rotationVector);
}

void RaceCar::render(mat4 view, mat4 projection) {
	carModel->draw(view, projection);
}

vec3 RaceCar::getPosition()
{
	return carModel->getPosition();
}

vec3 RaceCar::getForwardVector()
{
	return carModel->getForwardVector();
}

void RaceCar::setPosition(vec3 position) {
	carModel->setPosition(position);
}

void RaceCar::setRotation(vec3 rotation) {
	carModel->setRotation(rotation);
}

float RaceCar::getLeftTurnDegrees() {
	return this->leftTurnDegrees;
}

vec3 RaceCar::getFrontWheelsShift() {
	return this->frontWheelsShift;
}

vec3 RaceCar::getRearWheelsShift() {
	return this->rearWheelsShift;
}

void RaceCar::setController(RaceCarController* controller) {
	this->controller = controller;
}

void RaceCar::updateColliderPosition() {
	float x = 0.5f, z = 0.5f;
	this->colliderVertice[0].x = this->carModel->getPosition().x + x;
	this->colliderVertice[0].z = this->carModel->getPosition().z + z;
	this->colliderVertice[1].x = this->carModel->getPosition().x + -x;
	this->colliderVertice[1].z = this->carModel->getPosition().z + z;
	this->colliderVertice[2].x = this->carModel->getPosition().x + -x;
	this->colliderVertice[2].z = this->carModel->getPosition().z + -z;
	this->colliderVertice[3].x = this->carModel->getPosition().x + x;
	this->colliderVertice[3].z = this->carModel->getPosition().z + -z;
}

void RaceCar::setOpponents(std::vector<RaceCar*> opponents) {
	this->opponents = opponents;
}

bool RaceCar::isColliding() {
	Intersection inter;
	for (RaceCar* opponent : opponents) {
		for (int i = 0; i < 4; i++) {
			float x1, z1, x2, z2;
			x1 = this->colliderVertice[i].x;
			z1 = this->colliderVertice[i].z;
			x2 = this->colliderVertice[(i+1)%4].x;
			z2 = this->colliderVertice[(i+1)%4].z;
			for (int j = 0; j < 4; j++) {
				float x3, z3, x4, z4;
				x3 = opponent->colliderVertice[j].x;
				z3 = opponent->colliderVertice[j].z;
				x4 = opponent->colliderVertice[(j + 1) % 4].x;
				z4 = opponent->colliderVertice[(j + 1) % 4].z;
				if (inter.isIntersecting(x1, z1, x2, z2, x3, z3, x4, z4)) {
					afterCollision(opponent);
					return true;
				}
			}
		}
	}
	return false;
}

void RaceCar::afterCollision(RaceCar* opponent) {
	glm::vec3 opponentMovement, raceCarMovement;
	opponentMovement = opponent->physicalModel->getCurrentVelocity();
	raceCarMovement = this->physicalModel->getCurrentVelocity();
	this->physicalModel->setCurrentMovement(opponentMovement);
	opponent->physicalModel->setCurrentMovement(raceCarMovement);
	this->carModel->move(opponentMovement);
	opponent->carModel->move(raceCarMovement);
}

void RaceCar::setPhysicalModel(RaceCarPhysicalModel* physicalModel) {
	this->physicalModel = physicalModel;
}

vec3 RaceCar::rotatePhysicalModelVector(vec3 vector) {

	vec3 physicalModelVector = PhysicalModel::PHYSICAL_MODEL_FORWARD;
	vec3 forward = carModel->getForwardVector();

	vec2 firstVector = normalize(vec2(physicalModelVector.z, physicalModelVector.x));
	vec2 secondVector = normalize(vec2(forward.z, forward.x));

	float rotationAngle = orientedAngle(firstVector, secondVector);
	vec3 result = rotate(mat4(1.0f), rotationAngle, vec3(0, 1, 0)) * vec4(vector, 0);

	return result;
}

RaceCarPhysicalModel RaceCar::getPhysicalModel()
{
	return *physicalModel;
}

float RaceCar::getRotationY() {
	return carModel->getRotation().y;
}
