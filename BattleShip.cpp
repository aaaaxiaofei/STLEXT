#include "BattleShip.hpp"
#include <iostream>
using namespace std;

BattleShip::BattleShip() {
	vector<vector<int>> matrix(GRID_SIZE, vector<int>(GRID_SIZE, 0));
	board = move(matrix);

}

void BattleShip::print() {
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			// Hidden
			if (board[i][j] == 0)
				cout << " * ";
			// Is a ship
			else if (board[i][j] == 1)
				cout << " X ";
			// Is water
			else if (board[i][j] == -1)
				cout << " o ";  
		}
		cout << endl;
	}
}