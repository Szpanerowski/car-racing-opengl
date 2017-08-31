#pragma once
#include "Shader.h"
#include "Model.h"
#include "Drawable.h"


using namespace std;

/*
o o o o o o o o
o o o o o o o o
o o - - - - o o
o o | o o | o o
o o | o o | o o
o o - - - - o o
o o o o o o o o
o o o o o o o o
*/

class TerrainLoader
{
public:
	enum TerrainType { Road, Grass};
	TerrainLoader() {};
	TerrainLoader(int x, int z)
	{
		if (x >= 8)
			x = 8;
		if (z >= 8)
			z = 8;

		this->x = x;
		this->z = z;

		terrainArray = new  TerrainType *[x];
		for (int i = 0; i < x; i++)
			terrainArray[i] = new TerrainType[z];

		
		for (int i = 0; i<x; i+=2)
		{
			for (int j = 0; j < z; j += 2)
			{
				//rysowanie drogi na krawedziach
				if (i == 2 || i == x-4 ||  j==2 || j==z-4) {
					Drawable d = Drawable("road");
					//d.scale(0.1, 1, 0.1);
					d.translate(i, -0.5, j);
					vecTerrain.push_back(d);
					terrainArray[i][j] = Road;
				}
				//rysowanie trawy na reszcie pola
				else { 
					Drawable d = Drawable("terrain");
					//d.scale(0.1, 1, 0.1);
					d.translate(i, -0.5, j);
					vecTerrain.push_back(d);
					//terrainArray[i][j] = Grass;
				}
			}
		}

	}

	void draw(glm::mat4 view, glm::mat4 projection) {
		for (int i = 0; i < vecTerrain.size(); i++) {
			vecTerrain.at(i).draw(view, projection);
		}
	}

	TerrainType getTerrainType(int x, int z)
	{
		if(x>=0 && x<this->x && z>=0 && z<this->z)
		return terrainArray[x][z];
	}

private:
	int x;
	int z;
	TerrainType ** terrainArray;
	vector <Drawable> vecTerrain;
};
