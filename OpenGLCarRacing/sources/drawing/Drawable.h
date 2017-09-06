#pragma once
#include "drawing/model/Shader.h"
#include "drawing/model/Model.h"

#include "glm/gtc/type_ptr.hpp"


class Drawable
{
public:

	Drawable() {}

	Drawable(std::string name) {

		std::string path = "res/models/" + name + ".obj";
		ourModel = Model(path);
		shader = Shader("res/shaders/modelLoading.vs", "res/shaders/modelLoading.frag");
	}

	void draw(glm::mat4 view, glm::mat4 projection)
	{
		shader.Use();

		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

		// Draw the loaded model
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		ourModel.Draw(shader);
	}

	void scale(float x, float y, float z)
	{
		model = glm::scale(model, glm::vec3(x, y, z));
	}

	void rotate(float angle, float x, float y, float z)
	{
		model = glm::rotate(model, angle, glm::vec3(x, y, z));
	}

	void translate(float x, float y, float z)
	{
		model = glm::translate(model, glm::vec3(x, y, z));
	}


	Model getModel()
	{
		return ourModel;
	}

	Shader getShader()
	{
		return shader;
	}

private:
	Shader shader;
	Model ourModel;
	glm::mat4 model;
};