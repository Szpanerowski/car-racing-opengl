#pragma once
#include "Shader.h"
#include "Model.h"
#include "Drawable.h"


using namespace std;


class TerrainLoader
{
public:
	TerrainLoader() {};
	TerrainLoader(int x, int z)
	{
		this->x = x;
		this->z = z;

		for (int i = -x / 2; i<x/2; i++)
		{
			for (int j = -z / 2; j < z/2; j++)
			{
				Drawable d = Drawable("terrain");
				d.translate(i, -0.5, j);
				vecTerrain.push_back(d);
			}
		}

	}

	void draw(glm::mat4 view, glm::mat4 projection) {
		for (int i = 0; i < vecTerrain.size(); i++) {
			vecTerrain.at(i).draw(view, projection);
		}
	}

private:
	int x;
	int z;
	vector <Drawable> vecTerrain;
};
