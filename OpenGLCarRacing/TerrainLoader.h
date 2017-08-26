#pragma once
#include "Shader.h"
#include "Model.h"
#include "Drawable.h"


using namespace std;


class TerrainLoader
{
public:
	TerrainLoader() {};
	TerrainLoader(int x, int z, Drawable drawable)
	{
		this->x = x;
		this->z = z;
		this->drawable = drawable;

	}

	void draw(glm::mat4 view, glm::mat4 projection) {

		drawable.translate(-x / 2, -0.5f, -z / 2);

		for (int i = 0; i<x; i++)
		{
			for (int j = 0; j < z; j++)
			{
				drawable.translate(0, 0, 1);
				drawable.draw(view, projection);
			}
			drawable.translate(1, 0, -z);
		}
	}
private:
	int x;
	int z;
	Drawable drawable;
};
