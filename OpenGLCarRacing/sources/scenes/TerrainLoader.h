#pragma once
#include "Shader.h"
#include "Model.h"
#include "Drawable.h"

#include <vector>

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
	struct BreakPoint
	{
		float x;
		float z;
	};

	enum TerrainType { Road, Grass};
	TerrainLoader() {};
	TerrainLoader(int x, int z)
	{
		if (x <= 8)
			x = 8;
		if (z <= 8)
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
				if ((i == 2 || i == x-4 ||  j==2 || j==z-4) && i!=0 && j!=0 && i!=x-2 && j!=z-2) {
					Drawable* d = new Drawable("road");
					//d.scale(0.1, 1, 0.1);
					d->move(glm::vec3(i, -0.5, j));
					vecTerrain.push_back(d);
					terrainArray[i][j] = Road;
					terrainArray[i-1][j] = Road;
					terrainArray[i][j-1] = Road;
					terrainArray[i-1][j-1] = Road;
				}
				//rysowanie trawy na reszcie pola
				else { 
					Drawable* d = new Drawable("terrain");
					//d.scale(0.1, 1, 0.1);
					d->move(glm::vec3(i, -0.5, j));
					vecTerrain.push_back(d);
					//terrainArray[i][j] = Grass;
				}
			}
		}

	}

	void draw(glm::mat4 view, glm::mat4 projection) {
		for (int i = 0; i < vecTerrain.size(); i++) {
			vecTerrain.at(i)->draw(view, projection);
		}
	}

	TerrainType getTerrainType(int x, int z)
	{
		if (x >= 0 && x < this->x && z >= 0 && z < this->z)
		{
			//x = x + x % 2;
			//z = z + z % 2;
			return terrainArray[x][z];
		}
		else return Grass;
	}
	BreakPoint getNextBreakPoint(int i)
	{
		i = i % 8;
		float edge1 = 2.0f;
		float edge2 = z - 4.0f;
		float margin = 3.0f;
		float height = 1.0f;
		BreakPoint bp[8] = { bp[0].x = edge1 + margin, bp[0].z = edge1,
								bp[1].x = edge1 + height, bp[1].z = edge1 + height,
								bp[2].x = edge1, bp[2].z = edge2 - margin, 
								bp[3].x = edge1 + height, bp[3].z = edge2 - height, 
								bp[4].x = edge2 - margin, bp[4].z = edge2, 
								bp[5].x = edge2 - height, bp[5].z = edge2 - height, 
								bp[6].x = edge2, bp[6].z = edge1 + margin, 
								bp[7].x = edge2 - height, bp[7].z = edge1 + height, };
		return bp[i];
	}

private:
	int x;
	int z;
	float breakPoints[8][2];
	TerrainType ** terrainArray;
	std::vector<Drawable*> vecTerrain;
};
