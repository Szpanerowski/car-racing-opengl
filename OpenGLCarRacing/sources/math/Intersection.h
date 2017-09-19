#pragma once
#include "RaceCar.h"

class Intersection
{

private:
	struct point { float x; float y; };

	struct line { point s, e; };

	int middle(int a, int b, int c);

	float CCW(point a, point b, point c);

	bool intersect(line a, line b);

public:
	Intersection();

	bool isIntersecting(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4 );
};