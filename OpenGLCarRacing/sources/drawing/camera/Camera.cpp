#include "Camera.h"

using namespace glm;

Camera::Camera(float aspect, float fovy, float near, float far)
{
	this->aspect = aspect;
	this->fovy = fovy;
	this->nearPlane = near;
	this->farPlane = far;

	this->projectionMatrix = createProjectionMatrix();
}

Camera::Camera(vec3 position, vec3 focus, vec3 nose, float aspect, float fovy, float near, float far)
	: Camera(aspect, fovy, near, far)
{
	this->position = position;
	this->focus = focus;
	this->nose = nose;

	this->followedObject = nullptr;
	this->viewMatrix = calculateViewMatrix();
}

Camera::Camera(CameraFollowedObject* followedObject, float aspect, float fovy, float near, float far)
	: Camera(aspect, fovy, near, far)
{
	this->followedObject = followedObject;
	this->viewMatrix = calculateViewMatrix();
}

mat4 Camera::getViewMatrix()
{
	return this->viewMatrix;
}

mat4 Camera::getProjectionMatrix()
{
	return this->projectionMatrix;
}

void Camera::frameUpdate(float deltaTime)
{
	if (followedObject != nullptr)
		viewMatrix = calculateViewMatrix();
}

mat4 Camera::calculateViewMatrix()
{
	if (followedObject != nullptr) {
		
		vec3 followedForward = followedObject->getForwardVector();

		focus = followedObject->getPosition();
		position = focus - followedForward * 3.0f + vec3(0, 1.5, 0);
		nose = vec3(0, 1, 0);
	}
	
	return lookAt(position, focus, nose);
}

mat4 Camera::createProjectionMatrix()
{
	return perspective(fovy, aspect, nearPlane, farPlane);
}

vec3 Camera::getPosition() {
	return this->position;
}