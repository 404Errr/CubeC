#include <iostream>
#include "Point.h"

using namespace std;

Point::Point(int iX, int iY, int iZ) {
	x = iX;
	y = iY;
	z = iZ;
}

int Point::getX() {
	return x;
}

int Point::getY() {
	return y;
}

int Point::getZ() {
	return z;
}

void Point::print() {
	cout << x << " " << y << " " << z << endl;
}

Point* Point::getMoved(int xO, int yO, int zO) {
	return new Point(x+xO, y+yO, z+zO);
}

void Point::move(int xO, int yO, int zO) {
	x = x+xO;
	y = y+yO;
	z = z+zO;
}
