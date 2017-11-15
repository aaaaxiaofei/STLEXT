#ifndef SHIP_HPP
#define SHIP_HPP

class Ship{

private:
	int x;
	int y;
	int len;
	bool flag_vertical;

public:
	Ship() {}
	Ship(int xx, int yy, int l, bool vertical) {
		x = xx;
		y = yy;
		len = l;
		flag_vertical = vertical;
	}
	
	int X() {return x;}
	int Y() {return y;}
	int length() {return len;}
	bool isVertical() {return flag_vertical;}
};


#endif