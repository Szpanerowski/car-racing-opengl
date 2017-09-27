#include "Lighting.h"

using namespace glm;
using namespace std;

Lighting::Lighting(vec3 globalAmbient) {

	this->globalAmbient = globalAmbient;
}

void Lighting::addCarLightSource(CarLightSource carLightSource) {

	this->carLightSources.push_back(carLightSource);
}

vector<CarLightSource> Lighting::getCarLightSources() {
	return this->carLightSources;
}

void Lighting::setCarLightSources(vector<CarLightSource> carLightSources) {
	this->carLightSources = carLightSources;
}

vec3 Lighting::getViewerPosition() {
	return this->viewerPosition;
}

void Lighting::setViewerPosition(vec3 viewerPosition) {
	this->viewerPosition = viewerPosition;
}

vec3 Lighting::getGlobalAmbient() {
	return this->globalAmbient;
}

void Lighting::setGlobalAmbient(vec3 globalAmbient) {
	this->globalAmbient = globalAmbient;
}