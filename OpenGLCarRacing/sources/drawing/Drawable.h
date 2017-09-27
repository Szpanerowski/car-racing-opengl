#pragma once

#include "drawing/model/Shader.h"
#include "drawing/model/Model.h"
#include "drawing/camera/CameraFollowedObject.h"
#include "drawing/lighting/CachedLighting.h"

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

		model = glm::translate(model, position);
		model = model * calculateRotationMatrix();
		model = glm::scale(model, scaleFactor);

		return model;
	}

	glm::mat4 calculateRotationMatrix() {

		return glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0, 1, 0));
	}

	Drawable(glm::vec3 position, glm::vec3 forward, glm::vec3 rotation, glm::vec3 scale) {

		this->position = position;
		this->rotation = rotation;
		this->scaleFactor = scale;

		this->initialForwardVector = calculateRotationMatrix() * glm::vec4(forward, 0);
	}

	void initializeShaders(std::string shader) {

		std::string shadersPath = "resources/shaders/";
		std::string vertexShader = shadersPath + shader + ".vs";
		std::string fragmentShader = shadersPath + shader + ".frag";

		this->shader = Shader(vertexShader.c_str(), fragmentShader.c_str());
	}

public:

	Drawable(std::string name, std::string shader, glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 forward = glm::vec3(0, 0, 1), glm::vec3 rotation = glm::vec3(0, 0, 0), glm::vec3 scale = glm::vec3(1, 1, 1))
			: Drawable(position, forward, rotation, scale) {

		std::string path = "resources/models/" + name + ".obj";
		ourModel = Model(path);

		initializeShaders(shader);
	}

	void draw(glm::mat4 view, glm::mat4 projection, CachedLighting* lighting) {
		shader.Use();

		loadLighting(lighting);

		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

		// Draw the loaded model
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(calculateModelMatrix()));
		ourModel.Draw(shader);
	}

	void loadLighting(CachedLighting* lighting) {

		int size = lighting->lightSourcesCount;
		glm::vec3 globalAmbient = lighting->globalAmbient;
		glm::vec3 viewersPosition = lighting->viewerPosition;

		glUniform3fv(glGetUniformLocation(shader.Program, "lightPositions"), size, lighting->lightPositions.data());
		glUniform3fv(glGetUniformLocation(shader.Program, "lightDirections"), size, lighting->lightDirections.data());
		glUniform3fv(glGetUniformLocation(shader.Program, "lightColors"), size, lighting->lightColors.data());
		glUniform1fv(glGetUniformLocation(shader.Program, "lightAngles"), size, lighting->lightAngles.data());
		glUniform1i(glGetUniformLocation(shader.Program, "lightSourcesCount"), size);

		glUniform3f(glGetUniformLocation(shader.Program, "globalAmbient"), globalAmbient.x, globalAmbient.y, globalAmbient.z);
		glUniform3f(glGetUniformLocation(shader.Program, "viewersPosition"), viewersPosition.x, viewersPosition.y, viewersPosition.z);
	}

	void move(glm::vec3 vector) {

		position += vector;
	}

	void scale(glm::vec3 scaleFactor) {

		this->scaleFactor *= scaleFactor;
	}

	void rotate(glm::vec3 rotation) {

		this->rotation += rotation;
		
		for (int i = 0; i < 3; ++i) {

			float rot = this->rotation[i];
			long long div = rot / 360;

			rot -= div * 360;

			if (rot < 0)
				rot += 360;

			this->rotation[i] = rot;
		}
	}

	virtual glm::vec3 getPosition() {
		return this->position;
	}

	void setPosition(glm::vec3 position) {
		this->position = position;
	}

	glm::vec3 getRotation() {
		return this->rotation;
	}

	void setRotation(glm::vec3 rotation) {
		this->rotation = rotation;
	}

	virtual glm::vec3 getForwardVector() {

		glm::vec4 forwardVector4 = calculateRotationMatrix() * glm::vec4(initialForwardVector, 0);
		glm::vec3 result = glm::normalize(glm::vec3(forwardVector4));

		return result;
	}
};