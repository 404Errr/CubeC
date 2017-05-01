#include "Generator.h"

#include <stdlib.h>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <time.h>

#include "Data.h"


using namespace std;

void Generator::generate() {
//	long startTime = time(0);
	int clo = clock();
	//do stuff
	cout << WIDTH << "x" << HEIGHT << "x" << DEPTH << "\tpieces: " << PIECE_COUNT << "\tpiece size: " << PIECE_SIZE_MIN << "-" << PIECE_SIZE_MAX << endl;
	gen();
	cout << endl;
	cube->print();
//	cout << endl << (time(0)-startTime)/(float)1000 << " s" << endl;
	cout << endl << (clock() - clo)/(float)1000 << " s" << endl;
}

void Generator::gen() {
	vector<int> colors(WIDTH*HEIGHT*DEPTH);
	int colorI;
	int movesData[6][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {-1, 0, 0}, {0, -1, 0}, {0, 0, -1}};
	vector<vector<int> > moves(6, vector<int>(3));
	for (int i = 0;i<6;i++) for (int j = 0;j<3;j++) moves[i][j] = movesData[i][j];
	bool reset = true, full;
	do {
		if (reset) {
			reset = false;
			full = false;
			cube = new Layout(WIDTH, HEIGHT, DEPTH);
			point = new Point(WIDTH/2, HEIGHT/2, DEPTH/2);
			colorI = 0;
			setColorList(colors);
		}
		bool couldMove = false;
		random_shuffle(moves.begin(), moves.end());
		for (int i = 0;i<6;i++) {
			Point *tempPoint = point->getMoved(moves[i][0], moves[i][1], moves[i][2]);
			if (cube->inBounds(tempPoint->getX(), tempPoint->getY(), tempPoint->getZ())) {
				int newCubie = cube->get(tempPoint->getX(), tempPoint->getY(), tempPoint->getZ());
				if (newCubie==0||(newCubie==colors[colorI]&&rand()%2==0)) {
					point->move(moves[i][0], moves[i][1], moves[i][2]);
					couldMove = true;
					break;
				}
			}
		}
		if (!couldMove) reset = true;
		if (cube->get(point->getX(), point->getY(), point->getZ())!=colors[colorI]) {
			cube->set(point->getX(), point->getY(), point->getZ(), colors[colorI]);
			colorI++;
		}
		if (colorI==WIDTH*HEIGHT*DEPTH) full = cube->isFull();
		if (full&&!isValid()) reset = true;
	} while(reset||!full);
}

void Generator::setColorList(vector<int> &colorList) {
	int counts[PIECE_COUNT];
	for (int i = 0;i<PIECE_COUNT;i++) {
		counts[i] = PIECE_SIZE_MIN;
	}
	int total = PIECE_SIZE_MIN*PIECE_COUNT, size = WIDTH*HEIGHT*DEPTH;
	while (total<size) {
		int color = 1+rand()%PIECE_COUNT;
		if (counts[color]<PIECE_SIZE_MAX) {
			counts[color]++;
			total++;
		}
	}
	for (int i = 0;i<size;i++) colorList[i] = 0;
	int k = 0;
	for (int i = 0;i<PIECE_COUNT;i++) {
		for (int j = 0;j<counts[i];j++) {
			colorList[k] = i+1;
			k++;
		}
	}
}

bool Generator::isValid() {
	if (!RUN_CHECKS) return true;
	if ((CHECK_TOO_MANY_ON_PLANE||CHECK_FLAT)&&planeChecks()) {
//		if (PRINT_CHECK) cout << "flat/too many on plane" << endl;
		return false;
	}
//	if (CHECK_IDENTICAL&&hasIdentical()) {
//		if (PRINT_CHECK) cout << "identical" << endl;
//		return false;
//	}
	if ((CHECK_DIAGONAL_COLLISION||CHECK_SURROUND_COLLISION)&&hasCollision()) {
		if (PRINT_CHECK) cout << "collision" << endl;
		return false;
	}
	if (CHECK_2D&&has2DClusters()) {
		if (PRINT_CHECK) cout << "2d" << endl;
		return false;
	}
	if (CHECK_3D&&has3DClusters()) {
		if (PRINT_CHECK) cout << "3d" << endl;
		return false;
	}
	return true;
}

bool Generator::hasCollision() {
	for (int z = 0;z<cube->d();z++) {
		for (int y = 0;y<cube->h();y++) {
			for (int x = 0;x<cube->w();x++) {
				if (CHECK_DIAGONAL_COLLISION) for (int a = 0;a<3;a++) {
					int zOLimit = (a==0)?1:2, yOLimit = (a==1)?1:2, xOLimit = (a==2)?1:2;
					vector<int> colors = vector<int>(4);
					int i = 0;
					for (int zO = 0;zO<zOLimit;zO++) {
						for (int yO = 0;yO<yOLimit;yO++) {
							for (int xO = 0;xO<xOLimit;xO++) {
								if (!cube->inBounds(x+xO, y+yO, z+zO)) continue;
								colors[i] = cube->get(x+xO, y+yO, z+zO);
								i++;
							}
						}
					}
					if (i<4) continue;
					int tl = colors[0], tr = colors[1], bl = colors[2], br = colors[3];
					if ((!(tl==bl||tr==br||tl==tr||tr==br||!(tl==br||tr==bl)))||(tl==br&&tr==bl&&tl!=tr)) {
						return true;
					}
				}
				if (CHECK_SURROUND_COLLISION) for (int a = 0;a<3;a++) {
					int zOLimit = (a==0)?3:1, yOLimit = (a==1)?3:1, xOLimit = (a==2)?3:1;
					vector<int> colors = vector<int>(3);
					int i = 0;
					for (int zO = 0;zO<zOLimit;zO++) {
						for (int yO = 0;yO<yOLimit;yO++) {
							for (int xO = 0;xO<xOLimit;xO++) {
								if (!cube->inBounds(x+xO, y+yO, z+zO)) continue;
								colors[i] = cube->get(x+xO, y+yO, z+zO);
								i++;
							}
						}
					}
					if (i<3) continue;
					int f = colors[0], m = colors[1], l = colors[2];
					if (f==l&&f!=m) {
						cout << colors[0] << colors[1] << colors[2] << endl << endl;
						cube->print();
						cout << endl;
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Generator::hasIdentical() {
	return false;
}

bool Generator::has2DClusters() {
	int count = 0;
	for (int z = 0;z<cube->d();z++) {
		for (int y = 0;y<cube->h();y++) {
			for (int x = 0;x<cube->w();x++) {
				for (int a = 0;a<3;a++) {
					int zOLimit = (a==0)?1:2, yOLimit = (a==1)?1:2, xOLimit = (a==2)?1:2;
					vector<int> counts = vector<int>(PIECE_COUNT);
					for (int zO = 0;zO<zOLimit;zO++) {
						for (int yO = 0;yO<yOLimit;yO++) {
							for (int xO = 0;xO<xOLimit;xO++) {
								if (!cube->inBounds(x+xO, y+yO, z+zO)) continue;
								counts[cube->get(x+xO, y+yO, z+zO)-1]++;
							}
						}
					}
					for (unsigned int i = 0;i<counts.size();i++) {
						if (counts[i]==4) count++;
						if (count>MAX_2D_CLUSTERS) return true;
					}
				}
			}
		}
	}
	return false;
}

bool Generator::has3DClusters() {
	for (int z = 0;z<cube->d()-1;z++) {
		for (int y = 0;y<cube->h()-1;y++) {
			for (int x = 0;x<cube->w()-1;x++) {
				for (int a = 0;a<3;a++) {
					vector<int> counts = vector<int>(PIECE_COUNT);
					for (int zO = 0;zO<2;zO++) {
						for (int yO = 0;yO<2;yO++) {
							for (int xO = 0;xO<2;xO++) {
								counts[cube->get(x+xO, y+yO, z+zO)-1]++;
							}
						}
					}
					for (unsigned int i = 0;i<counts.size();i++) {
						if (counts[i]>MAX_3D_CUBIES) return true;
					}
				}
			}
		}
	}
	return false;
}

bool Generator::planeChecks() {
	vector<vector<vector<int> > > planeCounts = vector<vector<vector<int> > >(PIECE_COUNT, vector<vector<int> >(3));
	for (int p = 0;p<PIECE_COUNT;p++) {
		for (int j = 0;j<3;j++) planeCounts[p][j] = vector<int>((j==Z)?cube->d():(j==Y)?cube->h():cube->w());
	}
	for (int z = 0;z<cube->d();z++) {
		for (int y = 0;y<cube->h();y++) {
			for (int x = 0;x<cube->w();x++) {
				int cubieColor = cube->get(x, y, z);
				planeCounts[cubieColor-1][X][x]++;
				planeCounts[cubieColor-1][Y][y]++;
				planeCounts[cubieColor-1][Z][z]++;
			}
		}
	}
	int flatCount = 0;
	for (unsigned int p = 0;p<planeCounts.size();p++) {
		for (unsigned int j = 0;j<planeCounts[p].size();j++) {
			int count = 0;
			for (unsigned int k = 0;k<planeCounts[p][j].size();k++) {
				if (CHECK_TOO_MANY_ON_PLANE&&planeCounts[p][j][k]>=PLANE_COUNT) return true;
				if (planeCounts[p][j][k]!=0) {
					count++;
				}
			}
			if (count==1) {
				flatCount++;
			}
		}
	}
	return CHECK_FLAT&&flatCount!=0;
}












