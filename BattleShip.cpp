#include "BattleShip.hpp"
#include <iostream>
using namespace std;

BattleShip::BattleShip() {
	vector<vector<int>> matrix(GRID_SIZE, vector<int>(GRID_SIZE, 0));
	board = move(matrix);
	num_enemy = 0;
}

void BattleShip::print() {
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			// Hidden
			if (board[i][j] == 0)
				cout << " * ";
			// Is a ship
			else if (board[i][j] == 1)
				cout << " S ";
			// Is Attached
			else if (board[i][j] == 2)
				cout << " X ";
			// Is water
			else if (board[i][j] == -1)
				cout << " o ";  
		}
		cout << endl;
	}
	cout << endl;
}

void BattleShip::placeShip
 (const vector<Ship>& ships) 
{
	for (auto s : ships) {
		int x = s.X(), y = s.Y(), len = s.length();
		bool flag_vertical = s.isVertical();

		for (int i = 0; i < len; i++) {
			board[x][y] = 1;
			num_enemy++;

			if (flag_vertical) x++;
			else y++;
		}
	}
}

int BattleShip::attack
 (int strategy) 
 {
	int count = 0;
	switch(strategy) {
		case 0: count = linearSearch();
				break;

		default : cout << "Strategy " << strategy 
					   << " is not available." 
					   << endl;
	}

	// Print final state
	print();

	return count;
}

int BattleShip::linearSearch() 
{
	int attack = 0, hit = 0;

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			attack++;
			if (board[i][j] == 1) {
				board[i][j] = 2;
				if (++hit == num_enemy) return attack;
			}
			else board[i][j] = -1;
		}
	}
}

int BattleShip::attack_along_ship() {
	
}