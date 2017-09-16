#pragma once

#include "drawing/RenderedObject.h"
#include "drawing/UpdatedObject.h"
#include "drawing/Drawable.h"
#include "models/physics/PhysicalModel.h"

#include "drawing/camera/CameraFollowedObject.h"

#include "glm/vec3.hpp"

class RaceCarController;

class RaceCar : public RenderedObject, public UpdatedObject, public CameraFollowedObject {

private:

	RaceCarController* controller;
	PhysicalModel* physicalModel;

	Drawable* carModel;
	glm::vec3 position;

public:

	RaceCar(Drawable* carModel, PhysicalModel* physicalModel);

	void accelerate(float acceleration);
	void brake(float braking);
	void turn(float turnDirection);

	virtual void frameUpdate();
	virtual void render(glm::mat4 view, glm::mat4 projection);

	virtual glm::vec3 getPosition();
	virtual glm::vec3 getForwardVector();

	void setController(RaceCarController* controller);
	void setModel(Drawable* drawable);
};