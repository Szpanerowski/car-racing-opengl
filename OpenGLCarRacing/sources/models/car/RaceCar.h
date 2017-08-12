#pragma once

#include "drawing/VisualObject.h"
#include "drawing/FrameUpdateableObject.h"
#include "models/physics/PhysicalModel.h"

#include "glm/vec3.hpp"

class RaceCarController;

class RaceCar : public VisualObject, public FrameUpdateableObject {

private:

	RaceCarController* controller;
	PhysicalModel* physicalModel;

	glm::vec3 position;

public:

	RaceCar();
	RaceCar(glm::vec3 position);
	RaceCar(glm::vec3 position, PhysicalModel* physicalModel);

	void accelerate(glm::vec3 acceleration);

	virtual void frameUpdate();
	virtual void render();

	void setController(RaceCarController* controller);
};