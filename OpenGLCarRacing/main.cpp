#include <cstdio>

#define GLM_FORCE_RADIANS

#include "GL/glew.h"
#include "GL/glut.h"
#include "GL/freeglut.h"
#include "glm/gtc/type_ptr.hpp"

#include "input/InputHandler.h"
#include "racing/Race.h"
#include "scenes/RaceScene.h"

const char* windowTitle = "Super Ultra Car Racing";
const int windowWidth = 800;
const int windowHeight = 600;
const int windowPositionX = 300;
const int windowPositionY = 100;

void initializeGLUT(int *pargc, char* argv[]) {

	glutInit(pargc, argv);
	
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	// This option is set in order to execute instructions after glutMainLoop in main function
	// Default behaviour of original GLUT library was exiting the whole program after closing the game window
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition(windowPositionX, windowPositionY);
	glutInitWindowSize(windowWidth, windowHeight);

	glutCreateWindow(windowTitle);
}

void initializeGLEW() {

	GLenum err = glewInit();

	if (err != GLEW_OK) {

		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(1);
	}

	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	fprintf(stdout, "GLSL version = %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void initializeInputHandler() {

	InputHandler::ensureInitialized();
}

void initializeRaceGame() {

	Race* race = new Race(0, 0);
	RaceScene* raceScene = new RaceScene(race, windowWidth, windowHeight);

	raceScene->load();
}


int main(int argc, char* argv[]) {

	initializeGLUT(&argc, argv);
	initializeGLEW();

	initializeInputHandler();
	initializeRaceGame();

	glutMainLoop();
}