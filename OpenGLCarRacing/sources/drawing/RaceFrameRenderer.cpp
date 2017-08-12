#include "RaceFrameRenderer.h"

#include <gl/freeglut.h>

RaceFrameRenderer::RaceFrameRenderer() {
}

void RaceFrameRenderer::renderFrame() {

	glClearColor(1, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
}