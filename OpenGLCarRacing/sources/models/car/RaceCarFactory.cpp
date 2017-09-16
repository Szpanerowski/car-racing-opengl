#include "RaceCarFactory.h"
#include "models/controllers/PlayerRaceCarController.h"
#include "models/controllers/ComputerRaceCarController.h"

using namespace glm;

RaceCarFactory* RaceCarFactory::instance = nullptr;

RaceCarFactory* RaceCarFactory::getInstance() {

	if (instance == nullptr)
		instance = new RaceCarFactory();

	return instance;
}

RaceCarFactory::RaceCarFactory() {}

RaceCar* RaceCarFactory::createPlayerRaceCar(vec3 position) {
	
	RaceCar* raceCar = createRaceCar(position);
	RaceCarController* controller = new PlayerRaceCarController(raceCar);

	raceCar->setController(controller);

	return raceCar;
}

RaceCar* RaceCarFactory::createOpponentRaceCar(vec3 position) {
	
	RaceCar* raceCar = createRaceCar(position);
	RaceCarController* controller = new ComputerRaceCarController(raceCar);

	raceCar->setController(controller);
	
	return raceCar;
}

RaceCar* RaceCarFactory::createRaceCar(vec3 position) {

	PhysicalModel* physicalModel = new PhysicalModel();
	Drawable* carModel = new Drawable("car2", position, vec3(0, 0, -1));
	RaceCar* raceCar = new RaceCar(carModel, physicalModel);

	return raceCar;
}