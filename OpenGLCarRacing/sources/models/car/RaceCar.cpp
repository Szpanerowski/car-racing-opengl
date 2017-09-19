#include "RaceCar.h"
#include "models/controllers/RaceCarController.h"

#include <cstdio>

using namespace glm;

RaceCar::RaceCar() {
}

RaceCar::RaceCar(PhysicalModel* physicalModel)
	: RaceCar() {
	
	this->physicalModel = physicalModel;
}

void RaceCar::accelerate(float acceleration) {

	physicalModel->applyForce(getForwardVector() * acceleration, vec3(0, 0, 0));
}

void RaceCar::brake(float braking) {

	physicalModel->applyForce(getForwardVector() * -braking, vec3(0, 0, 0));
}

void RaceCar::turn(float turnLeftDirection) {

	physicalModel->applyForce(getForwardVector(), vec3(0, 1, 0) * turnLeftDirection);
}

void RaceCar::frameUpdate() {

	controller->frameUpdate();

	physicalModel->updatePhysics();

	//collisions
	updateColliderPosition();
	if (isColliding()) {
		afterCollision();
	}

	vec3 movementVector = physicalModel->getCurrentMovement();
	carModel->move(movementVector);

	vec3 rotationVector = physicalModel->getCurrentRotation();

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

void RaceCar::setController(RaceCarController* controller) {
	this->controller = controller;
}

void RaceCar::setModel(Drawable* carModel) {
	this->carModel = carModel;
	this->carModel->move(this->position);
}

void RaceCar::updateColliderPosition() {
	for (int i = 0; i < 4; i++) {
		this->colliderVertice[i].x = this->carModel->getPosition().x + 1.0f;
		this->colliderVertice[i].z = this->carModel->getPosition().z + 1.0f;
	}
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
					return true;
				}
			}
		}
	}
	return false;
}

void RaceCar::afterCollision() {
	this->physicalModel->stopMovement();
}

