#pragma once

#include "RaceCarController.h"
#include "models/car/RaceCar.h"

class PlayerRaceCarController : public RaceCarController
{
private:

	bool driveForward();
	bool driveBackward();
	bool turnLeft();
	bool turnRight();
	bool checkOppositeValues(bool primary, bool opposite);

public:

	PlayerRaceCarController(RaceCar* raceCar);

	virtual void frameUpdate();
};

