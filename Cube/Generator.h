#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <vector>

#include "Layout.h"
#include "Point.h"

namespace std {

class Generator {
	public:
		void generate();
		void gen();
		void setColorList(vector<int> &colorList);
		bool isValid();
		bool planeChecks();
//		bool hasFlat();
		bool hasIdentical();
		bool hasCollision();
		bool has2DClusters();
		bool has3DClusters();
//		bool tooManyOnPlane();
//		vector<vector<vector<int> > > getPlaneCounts();
	private:
		Layout *cube;
		Point *point;
};

}

#endif
