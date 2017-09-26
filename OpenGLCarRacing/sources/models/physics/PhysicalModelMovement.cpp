#include "PhysicalModelMovement.h"

using namespace glm;

PhysicalModelMovement::PhysicalModelMovement(vec3 velocity, vec3 rotation) {

	this->velocity = velocity;
	this->rotation = rotation;
}