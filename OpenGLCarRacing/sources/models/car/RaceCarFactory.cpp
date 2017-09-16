#include "RaceCarFactory.h"
#include "models/controllers/PlayerRaceCarController.h"
#include "models/controllers/ComputerRaceCarController.h"
#include "TerrainLoader.h"

using namespace glm;

RaceCarFactory* RaceCarFactory::instance = nullptr;

RaceCarFactory* RaceCarFactory::getInstance() {

	if (instance == nullptr)
		instance = new RaceCarFactory();

	return instance;
}

RaceCarFactory::RaceCarFactory() {}

RaceCar* RaceCarFactory::createPlayerRaceCar(vec3 position) {
	
	RaceCar* raceCar = createRaceCar(position, "car");
	RaceCarController* controller = new PlayerRaceCarController(raceCar);

	raceCar->setController(controller);

	return raceCar;
}

RaceCar* RaceCarFactory::createOpponentRaceCar(vec3 position, TerrainLoader* terrainLoader) {
	
	RaceCar* raceCar = createRaceCar(position, "car2");
	RaceCarController* controller = new ComputerRaceCarController(raceCar, terrainLoader);

	raceCar->setController(controller);
	
	return raceCar;
}

RaceCar* RaceCarFactory::createRaceCar(vec3 position, string model) {

	PhysicalModel* physicalModel = new PhysicalModel();
	RaceCar* raceCar = new RaceCar(physicalModel);
	Drawable* carModel = new Drawable(model, position, vec3(0, 0, -1));

	raceCar->setModel(carModel);

	return raceCar;
}