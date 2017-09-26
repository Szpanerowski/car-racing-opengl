#include "Scene.h"

#include "gl/freeglut.h"

int Scene::currentTime = 0;
Scene* Scene::currentScene = nullptr;

void Scene::load() {

	currentTime = glutGet(GLUT_ELAPSED_TIME);
	currentScene = this;
	
	glutDisplayFunc(renderFrame);
}

void Scene::renderFrame() {

	int time = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = time - currentTime;

	float deltaSeconds = (float)deltaTime / 1000;

	currentScene->update(deltaSeconds);
	currentScene->render();

	currentTime = glutGet(GLUT_ELAPSED_TIME);

	glutTimerFunc(5, timerTick, 0);
}

void Scene::timerTick(int value) {

	glutPostRedisplay();
}