#pragma once

#include "drawing/RenderedObject.h"
#include "drawing/UpdatedObject.h"
#include "drawing/Drawable.h"
#include "models/physics/RaceCarPhysicalModel.h"

#include "drawing/camera/CameraFollowedObject.h"

#include "glm/vec3.hpp"
#include "math/Intersection.h"

class RaceCarController;
class RaceCarPhysicalModel;

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
	RaceCarPhysicalModel* physicalModel;
	Drawable* carModel;

	glm::vec3 position;
	glm::vec3 frontWheelsShift;
	glm::vec3 rearWheelsShift;

	float leftTurnDegrees;
	float maxTurnDegrees;
	float engineMaxForce;

	glm::vec3 rotatePhysicalModelVector(glm::vec3);

public:

	RaceCar(Drawable* carModel);

	void accelerate(float acceleration);
	void turn(float turnDirection);

	virtual void frameUpdate(float deltaSeconds);
	virtual void render(glm::mat4 view, glm::mat4 projection);

	virtual glm::vec3 getPosition();
	virtual glm::vec3 getForwardVector();

	void updateColliderPosition();
	void setOpponents(std::vector<RaceCar*> opponents);
	bool isColliding();
	void afterCollision(RaceCar* opponent);

	void setPosition(glm::vec3 position);
	void setRotation(glm::vec3 rotation);

	glm::vec3 getFrontWheelsShift();
	glm::vec3 getRearWheelsShift();

	float getLeftTurnDegrees();

	void setController(RaceCarController* controller);
	void setPhysicalModel(RaceCarPhysicalModel* physicalModel);
};