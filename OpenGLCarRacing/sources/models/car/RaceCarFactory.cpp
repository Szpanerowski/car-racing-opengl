#include "RaceCarFactory.h"
#include "models/controllers/PlayerRaceCarController.h"
#include "models/controllers/ComputerRaceCarController.h"

RaceCarFactory* RaceCarFactory::instance = nullptr;

RaceCarFactory* RaceCarFactory::getInstance() {

	if (instance == nullptr)
		instance = new RaceCarFactory();

	return instance;
}

RaceCarFactory::RaceCarFactory() {}

RaceCar* RaceCarFactory::createPlayerRaceCar() {
	
	RaceCar* raceCar = createRaceCar();
	RaceCarController* controller = new PlayerRaceCarController(raceCar);

	return raceCar;
}

RaceCar* RaceCarFactory::createOpponentRaceCar() {
	
	RaceCar* raceCar = createRaceCar();
	RaceCarController* controller = new ComputerRaceCarController(raceCar);

	return raceCar;
}

RaceCar* RaceCarFactory::createRaceCar() {

	return new RaceCar();
}