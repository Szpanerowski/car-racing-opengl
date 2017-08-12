#include "RaceCarController.h"
#include "models/car/RaceCar.h"

RaceCarController::RaceCarController(RaceCar* raceCar) {

	this->raceCar = raceCar;
}

RaceCar* RaceCarController::getRaceCar() {
	return raceCar;
}