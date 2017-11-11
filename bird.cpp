#include <iostream>
#include "bird.hpp"
#include <cmath>
using namespace std;

Bird::Bird() {

}

Bird::Bird(double pos_x, double pos_y, double v_x, double v_y) {
	x = pos_x;
	y = pos_y;
	vx = v_x;
	vy = v_y;
}

Bird::~Bird() {

}

double Bird::getX() {
	return x;
}

double Bird::getY() {
	return y;
}

double Bird::getVX() {
	return vx;
}

double Bird::getVY() {
	return vy;
}

void Bird::move(const double dx, const double dy) {

	if (dx == 0.0 && dy == 0.0) return;
	
	double unit_x = dx / sqrt(dx*dx+dy*dy);
	double unit_y = dy / sqrt(dx*dx+dy*dy);
	x += unit_x * vx;
	y += unit_y * vy;
}

void Bird::print() {
	cout << "Bird at (" << x << "," << y << ") with speed (" 
		 << vx << "," << vy << ")" << endl;
}