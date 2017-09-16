#pragma once

#include "GL/glew.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "drawing/UpdatedObject.h"
#include "drawing/camera/CameraFollowedObject.h"

class Camera : UpdatedObject
{
private:

	glm::vec3 position;
	glm::vec3 focus;
	glm::vec3 nose;

	CameraFollowedObject* followedObject;

	float fovy;
	float aspect;
	float nearPlane;
	float farPlane;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	Camera(float aspect, float fovy, float near, float far);

	glm::mat4 calculateViewMatrix();
	glm::mat4 createProjectionMatrix();

public:

	Camera(glm::vec3 position, glm::vec3 focus, glm::vec3 nose, float aspect, float fovy = 45.0f, float near = 0.1f, float far = 100.0f);
	Camera(CameraFollowedObject* followedObject, float aspect, float fovy = 45.0f, float near = 0.1f, float far = 100.0f);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	virtual void frameUpdate();
};
