#pragma once

#include "RaceCarController.h"

class ComputerRaceCarController : public RaceCarController
{
public:
	ComputerRaceCarController(RaceCar* raceCar);

	virtual void frameUpdate();
};

