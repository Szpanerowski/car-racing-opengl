#include "Race.h"

#include <gl/freeglut.h>

Race::Race(int opponents, int laps, bool computerOnly) {

	this->opponentsCount = opponents;
	this->lapsCount = laps;
	this->computerOnly = computerOnly;
}

int Race::getOpponentsCount() {
	return this->opponentsCount;
}

int Race::getLapsCount() {
	return this->lapsCount;
}

bool Race::isComputerOnly() {
	return this->computerOnly;
}