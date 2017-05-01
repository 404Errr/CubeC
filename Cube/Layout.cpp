#include <vector>
#include <iostream>
#include "Layout.h"

using namespace std;

Layout::Layout(vector<vector<vector<int> > > layout) {
	cubies = layout;
}

Layout::Layout(int w, int h, int d) {
	cubies = vector<vector<vector<int> > > (d, vector<vector<int> >(h, vector<int>(w)));
}

int Layout::d() {
	return cubies.size();
}

int Layout::h() {
	return cubies[0].size();
}

int Layout::w() {
	return cubies[0][0].size();
}

void Layout::print() {
	for (int z = 0;z<d();z++) {
			for (int y = 0;y<h();y++) {
				for (int x = 0;x<w();x++) {
					cout << get(x, y, z);
				}
				cout << endl;
			}
			if (z<d()-1) {
				for (int i = 0;i<w();i++) cout << "-";
				cout << endl;
			}
		}
}

bool Layout::contains(int val) {
	for (int z = 0;z<d();z++) {
		for (int y = 0;y<h();y++) {
			for (int x = 0;x<w();x++) {
				if (get(x, y, z)==val) return true;
			}
		}
	}
	return false;
}

int Layout::get(int x, int y, int z) {
	return cubies[z][y][x];
}

void Layout::set(int x, int y, int z, int val) {
	cubies[z][y][x] = val;
}

bool Layout::inBounds(int x, int y, int z) {
	return x>=0&&y>=0&&z>=0&&x<w()&&y<h()&&z<d();
}

bool Layout::isFull() {
	for (int z = 0;z<d();z++) {
		for (int y = 0;y<h();y++) {
			for (int x = 0;x<w();x++) {
				if (get(x, y, z)==0) return false;
			}
		}
	}
	return true;
}

void Layout::rotate(int xRotations, int yRotations, int zRotations) {
		while (xRotations<0) xRotations+=4;
		while (yRotations<0) yRotations+=4;
		while (zRotations<0) zRotations+=4;
		for (int zR = 0;zR<zRotations;zR++) {
			vector<vector<vector<int> > > rotated = vector<vector<vector<int> > > (d(), vector<vector<int> >(h(), vector<int>(w())));
			for (int z = 0;z<d();z++) {
				for (int y = 0;y<w();y++) {
					for (int x = 0;x<h();x++) {
						rotated[z][y][x] = cubies[z][h()-x-1][y];
					}
				}
			}
			cubies = rotated;
		}
		for (int yR = 0;yR<yRotations;yR++) {
			vector<vector<vector<int> > > rotated = vector<vector<vector<int> > > (d(), vector<vector<int> >(h(), vector<int>(w())));
			for (int z = 0;z<w();z++) {
				for (int y = 0;y<h();y++) {
					for (int x = 0;x<d();x++) {
						rotated[z][y][x] = cubies[d()-x-1][y][z];
					}
				}
			}
			cubies = rotated;
		}
		for (int xR = 0;xR<xRotations;xR++) {
			vector<vector<vector<int> > > rotated = vector<vector<vector<int> > > (d(), vector<vector<int> >(h(), vector<int>(w())));
			for (int z = 0;z<h();z++) {
				for (int y = 0;y<d();y++) {
					for (int x = 0;x<w();x++) {
						rotated[z][y][x] = cubies[y][z][w()-1-x];
					}
				}
			}
			cubies = rotated;
		}
	}


