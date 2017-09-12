#include "Camera.h"

using namespace glm;

Camera::Camera(float aspect, float fovy, float near, float far)
{
	this->aspect = aspect;
	this->fovy = fovy;
	this->nearPlane = near;
	this->farPlane = far;

	this->projectionMatrix = perspective(fovy, aspect, near, far);
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

void Camera::frameUpdate()
{
	if (followedObject != nullptr)
		viewMatrix = calculateViewMatrix();
}

mat4 Camera::calculateViewMatrix()
{
	if (followedObject == nullptr)
		return lookAt(position, focus, nose);
	else
	{
		vec3 faceDirection = followedObject->getFaceVector();
		vec3 focusPosition = followedObject->getPosition();
		vec3 cameraPosition = focusPosition + vec3(0, 0, -1);

		return lookAt(cameraPosition, focusPosition, vec3(0, 0, 1));
	}
}