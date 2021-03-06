#pragma once

#include <vector>

#include "drawing/camera/Camera.h"
#include "models/car/RaceCar.h"
#include "racing/Race.h"
#include "Scene.h"
#include "scenes/TerrainLoader.h"
#include "drawing/lighting/Lighting.h"

class RaceScene : public Scene
{
private:

	TerrainLoader* terrainLoader;
	Camera* camera;
	Lighting* lighting;
	Race* race;

	std::vector<RaceCar*> raceCars;

	std::vector<CarLightSource> collectCarLights();

public:

	RaceScene(Race* race, int windowWidth, int windowHeight);

	virtual void update(float deltaSeconds);
	virtual void render();
};

