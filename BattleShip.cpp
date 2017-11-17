#include "BattleShip.hpp"
#include <iostream>
#include <stdlib.h> 
#include <time.h>  
using namespace std;

BattleShip::BattleShip() {
	vector<vector<int>> matrix(GRID_SIZE, vector<int>(GRID_SIZE, 0));
	board = move(matrix);

	vector<vector<int>> matrix2(GRID_SIZE, vector<int>(GRID_SIZE, 0));
	enemy = move(matrix2);

	num_enemy = 0;
	enemy_sum = 0;
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

void BattleShip::print2() {
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			// Hidden
			if (enemy[i][j] == 0)
				cout << " * ";
			// Is a ship
			else if (enemy[i][j] == 1)
				cout << " S ";
			// Is Attached
			else if (enemy[i][j] == 2)
				cout << " X ";
			// Is water
			else if (enemy[i][j] == -1)
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
		case 3: count = scoreSearch();
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
	return attack;
}

int BattleShip::gapSearch2() 
{

	int attack = 0, hit = 0;

	// first round attack
	for (int i = 0; i < board.size(); i += 2) {
		for (int j = 0; j < board[i].size(); j++) {

			if ((i+j)%4 != 2) continue;

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

	// Second round attack
	for (int i = 1; i < board.size(); i += 2) {
		for (int j = 0; j < board[i].size(); j++) {

			if ((i+j)%2 != 0) continue;

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

	// Third round attack
	for (int i = 0; i < board.size(); i += 2) {
		for (int j = 0; j < board[i].size(); j++) {

			if ((i+j)%4 != 0) continue;

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

	cout << "total hit time " << hit << endl;
	return attack;
}

int BattleShip::scoreSearch()
{

	int attack = 0;
	Cell c;
	vector<vector<Cell>> state(GRID_SIZE, vector<Cell>(GRID_SIZE, c));

	// Initialize score in each grid
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {

			state[i][j].left = j + 1;
			state[i][j].right = GRID_SIZE - j;
			state[i][j].up = i + 1;
			state[i][j].down = GRID_SIZE - i;

			int score_x = min(state[i][j].up, state[i][j].down) * 2; 
			int score_y = min(state[i][j].left, state[i][j].right) * 2; 

			state[i][j].value = score_x * score_y;
		}
	}

	int hit = 0;
	while (enemy_sum < 17) {
		// Search for largest score to attack
		int max_score = 0, max_i, max_j;
		for (int i = 0; i < GRID_SIZE; i++) {
			for (int j = 0; j < GRID_SIZE; j++) {
				if (state[i][j].value > max_score) {
					max_score = state[i][j].value;
					max_i = i;
					max_j = j;
				}
			}
		}

		// Attack max score cell
		if (board[max_i][max_j] == 0) {
			enemy[max_i][max_j] = -1;
			attack++;
			update(state, max_i, max_j);
		}
		else {
			enemy[max_i][max_j] = 2;
			enemy_sum++;
			attack++;

			// searchX(state, max_i, max_j);
			// searchY(state, max_i, max_j);
			search_neighbor(state, max_i, max_j);

			print2();

		}

		// print();
		

	}

	int result = 0;
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			if (enemy[i][j] != 0) {
				result++;
				enemy[i][j] = 0;
			}
		}
	}
	enemy_sum = 0;
	return result;
}

int BattleShip::search_neighbor(vector<vector<Cell>>& state, int x, int y) {

	update(state, x, y);

	vector<int> direction = {1, 0, -1, 0, 0, 1, 0, -1};

	for (int d = 0; d < direction.size(); d += 2) {
		int i = x + direction[d], j = y + direction[d+1];

		if (i >= 0 && i < GRID_SIZE && j >= 0 && j < GRID_SIZE && enemy[i][j] == 0 && state[i][j].value > 0) {
			if (board[i][j] == 1) {
				enemy[i][j] = 2;
				enemy_sum++;
				search_neighbor(state, i, j);
			}
			else {
				enemy[i][j] = -1;
				update(state, i, j);
			}
		}
	}
	return 0;
}

void BattleShip::update(vector<vector<Cell>>& state, int x, int y) {

	if (state[x][y].value == 0) return;

	state[x][y].setZero();

	vector<int> direction = {-1, 1};

	for (auto dx : direction) {
		for (int i = x + dx; i >= 0 && i < GRID_SIZE; i += dx) {
			int j = y;

			if (state[i][j].value == 0) break;

			state[i][j].up = i > 0 ? state[i-1][j].up + 1 : state[i][j].up;
			state[i][j].down = i < GRID_SIZE - 1 ? state[i+1][j].down + 1 : state[i][j].down;

			int score_x = min(state[i][j].up, state[i][j].down) * 2;
			int score_y = min(state[i][j].left, state[i][j].right) * 2;
			state[i][j].value = score_x * score_y;
		}
	}

	for (auto dy : direction) {
		for (int j = y + dy; j >= 0 && j < GRID_SIZE; j += dy) {
			int i = x;

			if (state[i][j].value == 0) break;


			state[i][j].left = j > 0 ? state[i][j-1].left + 1 : state[i][j].left;
			state[i][j].right = j < GRID_SIZE - 1 ? state[i][j+1].right + 1 : state[i][j].right;

			int score_x = min(state[i][j].up, state[i][j].down) * 2;
			int score_y = min(state[i][j].left, state[i][j].right) * 2;
			state[i][j].value = score_x * score_y;
		}
	}

}

int BattleShip::searchX(vector<vector<Cell>>& state, int x, int y)
{
	if (state[x][y].value == 0) return 0;
	update(state, x, y);
	int hit = 1, j = y;

	for (int i = x+1; i < GRID_SIZE; i++) {
		update(state, i, j);
		if (board[i][j] == 1) {
			enemy[i][j] = 2;
			enemy_sum++;
		}
		else {
			enemy[i][j] = -1;
			break;
		}
	}
	for (int i = x-1; i >=0 ; i--) {
		update(state, i, j);
		if (board[i][j] == 1) {
			enemy_sum++;
			enemy[i][j] = 2;
		}
		else {
			enemy[i][j] = -1;
			break;
		}
	}

	return hit;
}

int BattleShip::searchY(vector<vector<Cell>>& state, int x, int y)
{

	update(state, x, y);
	int hit = 1, i = x;

	for (int j = y+1; j < GRID_SIZE; j++) {
		update(state, i, j);
		if (board[i][j] == 1) {
			enemy_sum++;
			enemy[i][j] = 2;
		}
		else {
			enemy[i][j] = -1;
			break;
		}
	}
	for (int j = y-1; j >=0 ; j--) {
		update(state, i, j);
		if (board[i][j] == 1) {
			enemy_sum++;
			enemy[i][j] = 2;
		}
		else {
			enemy[i][j] = -1;
			break;
		}
	}
	
	return hit;
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