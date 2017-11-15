#include "BattleShip.hpp"
#include <iostream>
#include <stdlib.h> 
#include <time.h>  
using namespace std;

BattleShip::BattleShip() {
	vector<vector<int>> matrix(GRID_SIZE, vector<int>(GRID_SIZE, 0));
	board = move(matrix);
	num_enemy = 0;
	srand(time(NULL));
}

void BattleShip::clear() {

	for (int i = 0; i < GRID_SIZE; i++) 
		for (int j = 0; j < GRID_SIZE; j++)
			board[i][j] = 0;
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


void BattleShip::generate_random_ship
 (const vector<int>& length)
{
	/* initialize random seed: */
  	
  	int i = 0; 

  	vector<int> direction = {1, 0, 0, 1, -1, 0, 0, -1};

  	while (i < length.size()) {

  		int x = rand() % GRID_SIZE, y = rand() % GRID_SIZE, len = length[i];

  		for (int j = (rand()%2)*2; j < direction.size(); j += 2) {

  			int dx = direction[j], dy = direction[j+1];

  			int x_end = x + (len-1)*dx, y_end = y + (len-1)*dy;

  			// valid range, try to place a ship
  			if (x_end >= 0 && x_end < GRID_SIZE && y_end >= 0 && y_end < GRID_SIZE) {
  				int sum = 0;
  				for (int ix = min(x, x_end); ix <= max(x, x_end); ix++)
  					for (int iy = min(y, y_end); iy <= max(y, y_end); iy++)
  						sum += board[ix][iy];

  				// No other ships put on this path, new ship can be placed
  				if (sum == 0) {
	  				for (int ix = min(x, x_end); ix <= max(x, x_end); ix++)
	  					for (int iy = min(y, y_end); iy <= max(y, y_end); iy++) {
	  						board[ix][iy] = 1;
	  						num_enemy++;
	  					}
	  				i++;
	  				break; // break four direction for loop
  				}
  			}
  		}
  	}
}

int BattleShip::attack
 (int strategy) 
 {
	int count = 0;
	vector<vector<int>> board_backup(board);

	switch(strategy) {
		case 0: count = linearSearch();
				break;
		case 1: count = gapSearch();
				break;
		case 2: count = gapSearch2();
				break;

		default : cout << "Strategy " << strategy 
					   << " is not available." 
					   << endl;
	}

	// Print final state
	// print();

	// restore board to initial state
	board = board_backup;

	return count;
}

int BattleShip::linearSearch() 
{
	int attack = 0, hit = 0;

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {

			if (board[i][j] == 1) {
				attack_along_ship_dfs(i, j, attack, hit);
				if (hit == num_enemy) return attack;
			}
			else if (board[i][j] == 0) {
				board[i][j] = -1;
				attack++;
			}
		}
	}

	return attack;
}

int BattleShip::gapSearch() 
{

	int attack = 0, hit = 0;

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {

			if ((i+j)%2 == 0) continue;

			if (board[i][j] == 1) {
				attack_along_ship_dfs(i, j, attack, hit);
				if (hit == num_enemy) return attack;
			}
			else if (board[i][j] == 0) {
				board[i][j] = -1;
				attack++;
			}
		}
	}
}

int BattleShip::gapSearch2() 
{

	int attack = 0, hit = 0;

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {

			if ((i+j)%2 == 1) continue;

			if (board[i][j] == 1) {
				attack_along_ship_dfs(i, j, attack, hit);
				if (hit == num_enemy) return attack;
			}
			else if (board[i][j] == 0) {
				board[i][j] = -1;
				attack++;
			}
		}
	}
}

void BattleShip::attack_along_ship(int x, int y, int& attack, int& hit) {

	vector<int> direction = {1, 0, 0, 1, -1, 0, 0, -1};

	if ((x+1 < GRID_SIZE && board[x+1][y] > 0) || 
		(x-1 >= 0 && board[x-1][y] > 0)) {

		int cur = x;
		while (cur < GRID_SIZE && board[cur][y] > 0) {
			if (board[cur][y] == 1) {
				attack++;
				hit++;
				board[cur][y] = 2;
			}
			cur++;
		}
		if (cur < GRID_SIZE && board[cur][y] == 0) {
			board[cur][y] = -1;
			attack++;
		}
		// attack_along_ship(cur-1, y, attack, hit);

		cur = x-1;
		while (cur >= 0 && board[cur][y] > 0) {
			if (board[cur][y] == 1) {
				attack++;
				hit++;
				board[cur][y] = 2;
			}
			cur--;
		}
		if (cur >= 0 && board[cur][y] == 0) {
			board[cur][y] = -1;
			attack++;
		}
		// attack_along_ship(cur+1, y, attack, hit);
	}
	if ((y+1 < GRID_SIZE && board[x][y+1] > 0) || 
		(y-1 >= 0 && board[x][y-1] > 0)) {
		
		int cur = y;
		while (cur < GRID_SIZE && board[x][cur] > 0) {
			if (board[x][cur] == 1) {
				attack++;
				hit++;
				board[x][cur] = 2;
			}
			cur++;
		}
		if (cur < GRID_SIZE && board[x][cur] == 0) {
			board[x][cur] = -1;
			attack++;
		}
		// attack_along_ship(x, cur-1, attack, hit);

		cur = y-1;
		while (cur >= 0 && board[x][cur] > 0) {
			if (board[x][cur] == 1) {
				attack++;
				hit++;
				board[x][cur] = 2;
			}
			cur--;
		}
		if (cur >= 0 && board[x][cur] == 0) {
			board[x][cur] = -1;
			attack++;
		}
		// attack_along_ship(x, cur+1, attack, hit);
	}

}

void BattleShip::attack_along_ship_dfs
 (int x, int y, int& attack, int& hit) 
 {
 	vector<int> direction = {1, 0, 0, 1, -1, 0, 0, -1};

 	if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) {
 		
 		if (board[x][y] == 0) {
 			board[x][y] = -1;
 			attack++;
 		}
 		else if (board[x][y] == 1) {
 			hit++;
 			attack++;
 			board[x][y] = 2;
 			for (int i = 0; i < direction.size(); i += 2) {
 				attack_along_ship_dfs(x+direction[i], y+direction[i+1], attack, hit);
 			}
 		}

 	}
 }