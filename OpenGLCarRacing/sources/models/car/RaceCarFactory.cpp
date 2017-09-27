#include "RaceCarFactory.h"
#include "models/controllers/PlayerRaceCarController.h"
#include "models/controllers/ComputerRaceCarController.h"
#include "models/physics/RaceCarPhysicalModel.h"
#include "TerrainLoader.h"

using namespace glm;

RaceCarFactory* RaceCarFactory::instance = nullptr;

RaceCarFactory* RaceCarFactory::getInstance() {

	if (instance == nullptr)
		instance = new RaceCarFactory();

	return instance;
}

RaceCarFactory::RaceCarFactory() {}

RaceCar* RaceCarFactory::createPlayerRaceCar() {
	
	RaceCar* raceCar = createRaceCar("car2");
	RaceCarController* controller = new PlayerRaceCarController(raceCar);

	raceCar->setController(controller);

	return raceCar;
}

RaceCar* RaceCarFactory::createOpponentRaceCar(TerrainLoader* terrainLoader, int bp) {
	RaceCar* raceCar = createRaceCar("car");
	ComputerRaceCarController* controller = new ComputerRaceCarController(raceCar, terrainLoader);
	controller->setBp(bp);
	raceCar->setController(controller);
	
	return raceCar;
}

RaceCar* RaceCarFactory::createOpponentRaceCar(TerrainLoader* terrainLoader) {

	RaceCar* raceCar = createRaceCar("car");
	ComputerRaceCarController* controller = new ComputerRaceCarController(raceCar, terrainLoader);
	controller->setBp(0);
	raceCar->setController(controller);

	return raceCar;
}

RaceCar* RaceCarFactory::createRaceCar(string model) {

	Drawable* carModel = new Drawable(model, "race_car", vec3(0, 0, 0), vec3(0, 0, -1));
	RaceCar* raceCar = new RaceCar(carModel);

	float carMass = 1000;
	float carLength = 4;
	float carWidth = 2;

	RaceCarPhysicalModel* physicalModel = new RaceCarPhysicalModel(raceCar, carMass, carLength, carWidth);
	raceCar->setPhysicalModel(physicalModel);

	return raceCar;
}