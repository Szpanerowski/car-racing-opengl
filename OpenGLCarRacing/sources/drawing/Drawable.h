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

	glm::mat4 calculateModelMatrix() {

		glm::mat4 model = glm::mat4(
			glm::vec4(1, 0, 0, 0),
			glm::vec4(0, 1, 0, 0),
			glm::vec4(0, 0, 1, 0),
			glm::vec4(0, 0, 0, 1)
		);

		model = glm::scale(model, scaleFactor);

		for (int i = 0; i < 3; ++i) {

			glm::vec3 axis = glm::vec3(0, 0, 0);
			axis[i] = 1;

			model = glm::rotate(model, glm::radians(rotation[i]), axis);
		}

		model = glm::translate(model, position);

		return model;
	}

public:

	Drawable() {
	
		this->position = glm::vec3(0, 0, 0);
		this->rotation = glm::vec3(0, 0, 0);
		this->scaleFactor = glm::vec3(1, 1, 1);
	}

	Drawable(std::string name)
		: Drawable() {

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

	virtual glm::vec3 getPosition() {
		return this->position;
	}

	virtual glm::vec3 getFaceVector() {

		return glm::normalize(position);
	}
};