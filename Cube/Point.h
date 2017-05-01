#ifndef POINT_H_
#define POINT_H_

namespace std {

class Point {
	private:
		int x, y, z;
	public:
		Point(int iX, int iY, int iZ);
		int getX();
		int getY();
		int getZ();
		void move(int xO, int yO, int zO);
		Point* getMoved(int xO, int yO, int zO);
		void print();
};

}

#endif
