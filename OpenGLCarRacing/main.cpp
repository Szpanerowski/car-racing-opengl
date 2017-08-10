#include "GL/glew.h"
#include "GL/glut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <cstdio>

#include "rendering/FrameRenderer.h"
#include "rendering/RaceFrameRenderer.h"
#include "input/InputHandler.h"

const char* windowTitle = "Super Ultra Car Racing";
const int windowWidth = 800;
const int windowHeight = 600;
const int windowPositionX = 300;
const int windowPositionY = 100;

void renderFrame() {

	static FrameRenderer* frameRenderer = new RaceFrameRenderer();

	frameRenderer->renderFrame();
}

void initializeGLUT(int *pargc, char* argv[]) {

	glutInit(pargc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition(windowPositionX, windowPositionY);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow(windowTitle);

	glutDisplayFunc(renderFrame);
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

int main(int argc, char* argv[]) {

	initializeGLUT(&argc, argv);
	initializeGLEW();

	initializeInputHandler();

	glutMainLoop();
}