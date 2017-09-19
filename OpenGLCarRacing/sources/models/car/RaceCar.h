#pragma once

#include "drawing/RenderedObject.h"
#include "drawing/UpdatedObject.h"
#include "drawing/Drawable.h"
#include "models/physics/PhysicalModel.h"

#include "drawing/camera/CameraFollowedObject.h"

#include "glm/vec3.hpp"
#include "math/Intersection.h"

class RaceCarController;

class RaceCar : public RenderedObject, public UpdatedObject, public CameraFollowedObject {

private:

	struct ColliderVertice
	{
		float x;
		float z;
	};
	ColliderVertice colliderVertice[4];
	std::vector<RaceCar*> opponents;

	RaceCarController* controller;
	PhysicalModel* physicalModel;

	Drawable* carModel;
	glm::vec3 position;

public:

	RaceCar();
	RaceCar(PhysicalModel* physicalModel);

	void accelerate(float acceleration);
	void brake(float braking);
	void turn(float turnDirection);

	virtual void frameUpdate();
	virtual void render(glm::mat4 view, glm::mat4 projection);

	virtual glm::vec3 getPosition();
	virtual glm::vec3 getForwardVector();

	void setController(RaceCarController* controller);
	void setModel(Drawable* drawable);

	void updateColliderPosition();
	void setOpponents(std::vector<RaceCar*> opponents);
	bool isColliding();
	void afterCollision();
};