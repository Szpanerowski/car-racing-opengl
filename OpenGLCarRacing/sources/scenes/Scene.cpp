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
}