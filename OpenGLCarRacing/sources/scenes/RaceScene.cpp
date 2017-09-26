#include "RaceScene.h"
#include "models/car/RaceCarFactory.h"

#include "gl/freeglut.h"
#include "glm/vec3.hpp"

using namespace glm;

RaceScene::RaceScene(Race* race, int windowWidth, int windowHeight) {

	this->terrainLoader = new TerrainLoader(30, 30);
	this->race = race;

	if (!race->isComputerOnly()) {

		RaceCar* playerCar = RaceCarFactory::getInstance()->createPlayerRaceCar(vec3(-2, -0.5f, 2));
		raceCars.push_back(playerCar);

		RaceCar* opponentCar = RaceCarFactory::getInstance()->createOpponentRaceCar(vec3(2.5, -0.5f, 2.5), terrainLoader);
		raceCars.push_back(opponentCar);

		float cameraAspect = (float)windowWidth / windowHeight;
		camera = new Camera(vec3(0, 5, -10), vec3(0, 0, 0), vec3(0, 1, 0), (float) windowWidth / windowHeight);
		//camera = new Camera(playerCar, cameraAspect);

		for (RaceCar* raceCar : raceCars) {
			std::vector<RaceCar*> tempCars;
			for (RaceCar* raceCarOp : raceCars) {
				if (raceCarOp != raceCar) {
					tempCars.push_back(raceCarOp);
				}
			}
			raceCar->setOpponents(tempCars);
		}
	}
}

void RaceScene::update() {

	for (RaceCar* raceCar : raceCars) {

		raceCar->frameUpdate();
	}

	camera->frameUpdate();
}

void RaceScene::render() {

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);

	terrainLoader->draw(camera->getViewMatrix(), camera->getProjectionMatrix());

	for (RaceCar* raceCar : raceCars) {

		raceCar->render(camera->getViewMatrix(), camera->getProjectionMatrix());
	}

	glutSwapBuffers();
}
