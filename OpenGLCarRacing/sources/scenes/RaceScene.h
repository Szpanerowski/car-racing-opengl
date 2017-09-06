#pragma once

#include <vector>

#include "drawing/camera/Camera.h"
#include "models/car/RaceCar.h"
#include "racing/Race.h"
#include "Scene.h"

class RaceScene : public Scene
{
private:

	Camera* camera;
	Race* race;

	std::vector<RaceCar*> raceCars;

public:

	RaceScene(Race* race);

	virtual void update();
	virtual void render();
};

