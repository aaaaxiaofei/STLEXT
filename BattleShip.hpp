#ifndef BATTLESHIP_HPP
#define BATTLESHIP_HPP

#include <vector>
using namespace std;

const int GRID_SIZE = 10;

class BattleShip {

private:
	vector<vector<int>> board;

public:
	BattleShip();
	~BattleShip() {};

	void print();


};
#endif