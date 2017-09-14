#include "Camera.h"

using namespace glm;

Camera::Camera(float aspect, float fovy, float near, float far)
{
	this->aspect = aspect;
	this->fovy = fovy;
	this->nearPlane = near;
	this->farPlane = far;

	this->position = vec3(0, 0, 5);
	this->focus = vec3(0, 0, 0);
	this->nose = vec3(0, 1, 0);

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

void Camera::frameUpdate()
{
	if (followedObject != nullptr)
		viewMatrix = calculateViewMatrix();
}

mat4 Camera::calculateViewMatrix()
{
	return lookAt(position, focus, nose);

	if (followedObject == nullptr)
		return lookAt(position, focus, nose);
	else
	{
		vec3 faceDirection = followedObject->getFaceVector();
		vec3 focusPosition = followedObject->getPosition();
		vec3 cameraPosition = focusPosition - faceDirection;

		return lookAt(cameraPosition, focusPosition, vec3(0, 1, 0));
	}
}

mat4 Camera::createProjectionMatrix()
{
	/*mat4 out;

	const float
		y_scale = 1.0f / tan(glm::radians(fovy / 2)),
		x_scale = y_scale / aspect,
		frustum_length = farPlane - nearPlane;

	out[0][0] = x_scale;
	out[1][1] = y_scale;
	out[2][2] = -((farPlane + nearPlane) / frustum_length);
	out[2][3] = -1;
	out[3][2] = -((2 * nearPlane * farPlane) / frustum_length);
	out[3][3] = 0;

	return out;*/
	return perspective(fovy, aspect, nearPlane, farPlane);
}