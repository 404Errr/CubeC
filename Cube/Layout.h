#ifndef LAYOUT_H_
#define LAYOUT_H_

namespace std {

class Layout {
	protected:
		vector<vector<vector<int> > > cubies;
	public:
		Layout(int w, int h, int d);
		Layout(vector<vector<vector<int> > > layout);
		void trim();
		void rotate(int xRotations, int yRotations, int zRotations);
		int get(int x, int y, int z);
		void set (int x, int y, int z, int val);
		int d();
		int h();
		int w();
		bool contains(int val);
		bool isFull();
		bool inBounds(int x, int y, int z);
		void print();
};

}

#endif
