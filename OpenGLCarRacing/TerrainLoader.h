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

		int a = 3; //dodatkowy obszar na zewnatrz drogi
		for (int i = -x / 2 -a; i<x/2+a; i++)
		{
			for (int j = -z / 2-a; j < z/2+a; j++)
			{
				//rysowanie drogi na krawedziach
				if (i == -x / 2 || i == x / 2 - 1 || j==-z/2 || j==z/2-1) { 
					Drawable d = Drawable("road");
					//d.scale(0.1, 1, 0.1);
					d.translate(i, -0.5, j);
					vecTerrain.push_back(d);
				}
				//rysowanie trawy na reszcie pola
				else { 
					Drawable d = Drawable("terrain");
					//d.scale(0.1, 1, 0.1);
					d.translate(i, -0.5, j);
					vecTerrain.push_back(d);
				}
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
