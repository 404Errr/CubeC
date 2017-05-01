#include <stdlib.h>
#include <ctime>
#include <iostream>

#include "Generator.h"

using namespace std;

int FUNCTION = 0;

int main() {
	srand(time(0));
	switch (FUNCTION) {
	case 0:
		cout << "Generating..." << endl;
		Generator gen;
		gen.generate();
		break;
	}
	return 0;
}






