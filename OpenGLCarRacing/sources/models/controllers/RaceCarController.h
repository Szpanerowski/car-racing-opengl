#pragma once

class RaceCar;

class RaceCarController {

private:

	RaceCar* raceCar;

public:

	RaceCarController(RaceCar* raceCar);

	virtual void frameUpdate() = 0;

	RaceCar* getRaceCar();
};