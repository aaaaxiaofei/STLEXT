#ifndef CELL_HPP
#define CELL_HPP

struct Cell {
	int left;
	int right;
	int up;
	int down;
	int value;

	Cell () {
		left = 0;
		right = 0;
		up = 0;
		down = 0;
		value = 0;
	}

	void setZero() {
		left = 0;
		right = 0;
		up = 0;
		down = 0;
		value = 0;
	}
};

#endif