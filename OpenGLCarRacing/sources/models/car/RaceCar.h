#pragma once

#include "drawing/RenderedObject.h"
#include "drawing/UpdatedObject.h"
#include "drawing/Drawable.h"
#include "models/physics/RaceCarPhysicalModel.h"

#include "drawing/camera/CameraFollowedObject.h"

#include "glm/vec3.hpp"

class RaceCarController;
class RaceCarPhysicalModel;

class RaceCar : public RenderedObject, public UpdatedObject, public CameraFollowedObject {

private:

	RaceCarController* controller;
	RaceCarPhysicalModel* physicalModel;
	Drawable* carModel;

	glm::vec3 position;
	glm::vec3 turnVector;
	glm::vec3 frontWheelsShift;

	static const int MAX_TURN_DEGREES = 45;

	glm::vec3 rotatePhysicalModelVector(glm::vec3);

public:

	RaceCar(Drawable* carModel);

	void accelerate(float acceleration);
	void turn(float turnDirection);

	virtual void frameUpdate();
	virtual void render(glm::mat4 view, glm::mat4 projection);

	glm::vec3 getPosition();
	glm::vec3 getForwardVector();
	glm::vec3 getTurnVector();

	void setController(RaceCarController* controller);
	void setPhysicalModel(RaceCarPhysicalModel* physicalModel);

	glm::vec3 getFrontWheelsShift();
};