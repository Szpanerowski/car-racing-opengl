#include "GL/glew.h"
#include "GL/glut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <cstdio>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Drawable.h"

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
Drawable car2;

void displayFrame() {

	glClearColor(1, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	car.scale(0.4f, 0.4f, 0.4f);
	car.translate(-2.0f, 0, 0);
	car.draw(camera.GetViewMatrix(), projection);

	car2.scale(0.4f, 0.4f, 0.4f);
	car2.translate(2.0f, 0, 0);
	car2.draw(camera.GetViewMatrix(), projection);

	//swap buffers
	glutSwapBuffers();
}

void initializeGLUT(int *pargc, char* argv[]) {

	glutInit(pargc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition(windowPositionX, windowPositionY);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow(windowTitle);

	glutDisplayFunc(displayFrame);
}

void initializeGLEW() {

	GLenum err = glewInit();

	if (err != GLEW_OK) {

		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(1);
	}

	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
}


int main(int argc, char* argv[]) {

	initializeGLUT(&argc, argv);
	initializeGLEW();

	glViewport(0, 0, windowWidth, windowHeight);
	glEnable(GL_DEPTH_TEST);
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, windowWidth, windowHeight);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);

	// Setup and compile our shaders

	projection = glm::perspective(camera.GetZoom(), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);


	car = Drawable("mustang");
	car2 = Drawable("mustang");

	glutMainLoop();

}