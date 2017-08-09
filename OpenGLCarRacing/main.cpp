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

#include "SOIL2/SOIL2.h"

const char* windowTitle = "Super Ultra Car Racing";
const int windowWidth = 800;
const int windowHeight = 600;
const int windowPositionX = 300;
const int windowPositionY = 100;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

void displayFrame() {

	glClearColor(1, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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


	Shader shader("res/shaders/modelLoading.vs", "res/shaders/modelLoading.frag");
	// Load models
	Model ourModel("res/models/nanosuit.obj");


	glutMainLoop();

}