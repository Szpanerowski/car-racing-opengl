#include "Scene.h"

#include "gl/freeglut.h"

Scene* Scene::currentScene = nullptr;

void Scene::load() {

	currentScene = this;
	glutDisplayFunc(renderFrame);
}

void Scene::renderFrame() {

	currentScene->update();
	currentScene->render();

	glutTimerFunc(17, timerTick, 0);
}

void Scene::timerTick(int value) {

	glutPostRedisplay();
}