#pragma once

#include "drawing/model/Shader.h"
#include "drawing/model/Model.h"
#include "drawing/camera/CameraFollowedObject.h"

#include "glm/gtc/type_ptr.hpp"

class Drawable : public CameraFollowedObject
{

private:

	Shader shader;
	Model ourModel;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scaleFactor;

	glm::vec3 initialForwardVector;

	glm::mat4 calculateModelMatrix() {
	
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::scale(model, scaleFactor);
		model = glm::translate(model, position);
		model = model * calculateRotationMatrix();
	

		return model;
	}

	glm::mat4 calculateRotationMatrix() {

		glm::mat4 rotationMatrix = glm::mat4();

		for (int i = 0; i < 3; ++i) {

			glm::vec3 axis = glm::vec3(0, 0, 0);
			axis[i] = 1;

			rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation[i]), axis);
		}

		return rotationMatrix;
	}

	Drawable(glm::vec3 position, glm::vec3 forward, glm::vec3 rotation, glm::vec3 scale) {

		this->position = position;
		this->rotation = rotation;
		this->scaleFactor = scale;
		this->initialForwardVector = forward;
	}

public:

	

	Drawable(std::string name, glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 forward = glm::vec3(0, 0, 1), glm::vec3 rotation = glm::vec3(0, 0, 0), glm::vec3 scale = glm::vec3(1, 1, 1))
			: Drawable(position, forward, rotation, scale) {

		std::string path = "resources/models/" + name + ".obj";
		ourModel = Model(path);
		shader = Shader("resources/shaders/modelLoading.vs", "resources/shaders/modelLoading.frag");
	}

	void draw(glm::mat4 view, glm::mat4 projection) {
		shader.Use();

		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

		// Draw the loaded model
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(calculateModelMatrix()));
		ourModel.Draw(shader);
	}

	void move(glm::vec3 vector) {

		position += vector;
	}

	void scale(glm::vec3 scaleFactor) {

		this->scaleFactor *= scaleFactor;
	}

	void rotate(glm::vec3 rotation) {

		this->rotation += rotation;
	}

	virtual glm::vec3 getPosition() {
		return this->position;
	}

	virtual glm::vec3 getForwardVector() {

		glm::vec4 forwardVector4 = calculateRotationMatrix() * glm::vec4(initialForwardVector, 0);

		return glm::normalize(glm::vec3(forwardVector4));
	}
};