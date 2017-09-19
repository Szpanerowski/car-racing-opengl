#include "Intersection.h"
#include <cstdio>

Intersection::Intersection() {
}

int Intersection::middle(int a, int b, int c) {
	int t;
	if (a > b) {
		t = a;
		a = b;
		b = t;
	}
	if (a <= c && c <= b) return 1;
	return 0;
}

float Intersection::CCW(point a, point b, point c)
{
	return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

bool Intersection::intersect(line a, line b) {
	if ((CCW(a.s, a.e, b.s) * CCW(a.s, a.e, b.e) < 0) &&
		(CCW(b.s, b.e, a.s) * CCW(b.s, b.e, a.e) < 0)) return true;

	if (CCW(a.s, a.e, b.s) == 0 && middle(a.s.x, a.e.x, b.s.x) && middle(a.s.y, a.e.y, b.s.y)) return true;
	if (CCW(a.s, a.e, b.e) == 0 && middle(a.s.x, a.e.x, b.e.x) && middle(a.s.y, a.e.y, b.e.y)) return true;
	if (CCW(b.s, b.e, a.s) == 0 && middle(b.s.x, b.e.x, a.s.x) && middle(b.s.y, b.e.y, a.s.y)) return true;
	if (CCW(b.s, b.e, a.e) == 0 && middle(b.s.x, b.e.x, a.e.x) && middle(b.s.y, b.e.y, a.e.y)) return true;

	return false;
}

bool Intersection::isIntersecting(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	point a, b, c, d;
	a.x = x1;
	a.y = y1;
	b.x = x2;
	b.y = y2;
	c.x = x3;
	c.y = y3;
	d.x = x4;
	d.y = y4;
	line l1, l2;
	l1.e = a;
	l1.s = b;
	l2.e = c;
	l2.s = d;
	return intersect(l1, l2);
}