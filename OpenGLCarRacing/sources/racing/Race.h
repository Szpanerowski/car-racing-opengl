#pragma once

class Race
{
private:

	int opponentsCount;
	int lapsCount;
	bool computerOnly;

public:

	Race(int opponents, int laps, bool computerOnly = false);

	int getOpponentsCount();
	int getLapsCount();
	bool isComputerOnly();
};

