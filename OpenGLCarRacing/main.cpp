#include "GL/glew.h"
#include "GL/glut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <cstdio>

#include "drawing/FrameRenderer.h"
#include "drawing/RaceFrameRenderer.h"
#include "input/InputHandler.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Drawable.h"
#include "TerrainLoader.h"

#include "SOIL2/SOIL2.h"

const char* windowTitle = "Super Ultra Car Racing";
const int windowWidth = 800;
const int windowHeight = 600;
const int windowPositionX = 300;
const int windowPositionY = 100;

glm::mat4 projection;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
Drawable car;
TerrainLoader terrain;

void renderFrame() {

	glClearColor(1, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	car.draw(camera.GetViewMatrix(), projection);

	terrain.draw(camera.GetViewMatrix(), projection);

	glutSwapBuffers();
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

	glViewport(0, 0, windowWidth, windowHeight);
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	glViewport(0, 0, windowWidth, windowHeight);
	glEnable(GL_DEPTH_TEST);
	projection = glm::perspective(camera.GetZoom(), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	car = Drawable("car");
	car.translate(0, -0.5f, 1);
	car.rotate(-45, 0, 1, 0);
	car.scale(0.5, 0.5, 0.5);

	terrain = TerrainLoader(15, 4);

	glutMainLoop();

}