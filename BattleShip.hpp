#ifndef BATTLESHIP_HPP
#define BATTLESHIP_HPP

#include <vector>
#include "Ship.hpp"
#include "Cell.hpp"
using namespace std;

const int GRID_SIZE = 10;

class BattleShip {

private:
	vector<vector<int>> board;
	vector<vector<int>> enemy;
	int enemy_sum;
	int num_enemy;

	// Attack Strategies
	int linearSearch();
	int gapSearch();
	int gapSearch2();
	int scoreSearch();
	void update(vector<vector<Cell>>& state, int i, int j);
	int searchX(vector<vector<Cell>>& state, int i, int j);
	int searchY(vector<vector<Cell>>& state, int i, int j);
	int search_neighbor(vector<vector<Cell>>& state, int i, int j);


	void attack_along_ship
		(int x, int y, int& attack, int& hit);

	void attack_along_ship_dfs
		(int x, int y, int& attack, int& hit);

public:
	BattleShip();
	~BattleShip() {};

	void print();
	void print2();
	void clear();

	void placeShip
		(const vector<Ship>& ships);

	void generate_random_ship
		(const vector<int>& length);

	int attack
		(int strategy);




};
#endif