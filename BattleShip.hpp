#ifndef BATTLESHIP_HPP
#define BATTLESHIP_HPP

#include <vector>
#include "Ship.hpp"
using namespace std;

const int GRID_SIZE = 10;

class BattleShip {

private:
	vector<vector<int>> board;
	int num_enemy;

	// Attack Strategies
	int linearSearch();
	int attack_along_ship();

public:
	BattleShip();
	~BattleShip() {};

	void print();
	void placeShip(const vector<Ship>& ships);
	int attack(int strategy);


};
#endif