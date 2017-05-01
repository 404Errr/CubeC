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
	cout << endl << (clock() - clo) << endl;
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
	if (planeChecks()) {
		if (PRINT_CHECK) cout << "flat/too many on plane" << endl;
		return false;
	}
//	if (hasIdentical()) {
//		if (PRINT_CHECK) cout << "identical" << endl;
//		return false;
//	}
//	if (hasCollision()) {
//		if (PRINT_CHECK) cout << "collision" << endl;
//		return false;
//	}
	if (has2DClusters()) {
		if (PRINT_CHECK) cout << "2d" << endl;
		return false;
	}
//	if (has3DClusters()) {
//		if (PRINT_CHECK) cout << "3d" << endl;
//		return false;
//	}
	return true;
}

//bool Generator::hasFlat() {
//	vector<vector<vector<int> > > planeCounts = getPlaneCounts();
//	int flatCount = 0;
//	for (unsigned int p = 0;p<planeCounts.size();p++) {
//		for (unsigned int j = 0;j<planeCounts[p].size();j++) {
//			int count = 0;
//			for (unsigned int k = 0;k<planeCounts[p][j].size();k++) {
//				if (planeCounts[p][j][k]!=0) {
//					count++;
//				}
//			}
//			if (count==1) {
//				flatCount++;
//			}
//		}
//	}
//	return flatCount!=0;
//}

bool Generator::hasCollision() {
	return false;//TODO
}

bool Generator::hasIdentical() {
	return false;//TODO
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
						if (counts[i]>=4) count++;
						if (count>MAX_2D_CLUSTERS) return true;
					}
				}
			}
		}
	}
	return false;
}

bool Generator::has3DClusters() {
	return false;
}

//bool Generator::tooManyOnPlane() {
//	bool tooManyOnPlane = false;
//	vector<vector<vector<int> > > planeCounts = getPlaneCounts();
//	for (unsigned int p = 0;p<planeCounts.size();p++) {
//		for (unsigned int j = 0;j<planeCounts[p].size();j++) {
//			for (unsigned int k = 0;k<planeCounts[p][j].size();k++) {
//				if (planeCounts[p][j][k]>=BORING_PLANE_COUNT) tooManyOnPlane = true;
//			}
//		}
//	}
//	return tooManyOnPlane;
//}

/*vector<vector<vector<int> > >*/bool Generator::planeChecks() {
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
				if (planeCounts[p][j][k]>=BORING_PLANE_COUNT) return true;
				if (planeCounts[p][j][k]!=0) {
					count++;
				}
			}
			if (count==1) {
				flatCount++;
			}
//			cout << p+1 << ", " << j << ", " << k << "\t" << planeCounts[p][j][k] << endl;
		}
	}
	return flatCount!=0;
}












