#pragma once
#include <cmath>
struct vector2 {
	double x, y;
	vector2() {}
	vector2(double X, double Y) { x = X; y = Y; }
};
double norm(vector2 p) {
	return sqrt(p.x*p.x + p.y*p.y);
}
vector2 operator+(vector2 a, vector2 b) {
	return vector2(a.x + b.x, a.y + b.y);
}
vector2 operator-(vector2 a, vector2 b) {
	return vector2(a.x - b.x, a.y - b.y);
}
vector2 operator*(vector2 a, double s) {
	return vector2(a.x*s, a.y*s);
}