#include <iostream>
#include <vector>
#include "bird.hpp"
#include "Queue.hpp"
#include "Job.hpp"
#include "function.hpp"
#include "Vector.hpp"
#include <string>
#include <exception>
#include "BattleShip.hpp"
#include <stdlib.h> 
#include <time.h> 

using namespace std;
void test_round_robin();
void battle_ship();


double divide(double a, double b) {

	if (b == 0) throw "divide zero";
	return a/b;
}

int main() {

	cout << "hello main" << endl;

	// test_round_robin();
	battle_ship();


	return 0;
}

void test_round_robin() {

	Job j1(1,0,5), j2(2,1,5), j3(3,5,3), j4(4, 6, 2);
	int quantum = 1, cur_time = 0;

	deque<Job> job_queue;
	deque<Job> done_queue;

	job_queue.push_back(j1);
	job_queue.push_back(j2);
	job_queue.push_back(j3);

	round_robin(job_queue, done_queue, quantum, cur_time);
}

void battle_ship() {

	// Initial Board
	
	// B.print();

	BattleShip B;

	// Place ships
	// Ship s1(7, 1, 4, false);
	// Ship s2(5, 5, 5, true);
	// Ship s3(4, 7, 3, false);
	// Ship s4(8, 7, 2, true);
	// Ship s5(7, 9, 3, true);
	// vector<Ship> ships = {s1, s2, s3, s4, s5};
	
	// B.placeShip(ships);

	// Random generate ships
	vector<int> length = {5, 4, 3, 3, 2};

	int num_method = 4, num_test = 10;
	vector<int> method(num_method, 0);

	
	// BattleShip B;
	for (int k = 0; k < num_test; k++) {
		
		cout << "\n ======= test " << k << " =======" << endl;

		B.clear();
		B.generate_random_ship(length);
		B.print();

		for (int i = 0; i < num_method; i++) {
			int count;
			count = B.attack(i);
			method[i] += count;
			cout << "Strategy " << i << " Total attack time: " << count << endl;
		}
		cout << endl;

		// int count = B.attack(3);
		// cout << "Strategy score total attack time " << count << endl;

	}	

	for (int k = 0; k < num_method; k++) {
		cout << "Strategy " << k << " average attack time: " << (double) method[k] / (double) num_test << endl;
	}


}

// A hard case:
// 	Ship s1(1, 0, 3, true);
// 	Ship s2(5, 3, 3, true);
// 	Ship s3(3, 6, 4, true);
// 	Ship s4(1, 9, 5, true);
// 	Ship s5(9, 2, 2, false);


// A even harder one
	// Ship s1(4, 0, 4, false);
	// Ship s2(9, 1, 5, false);
	// Ship s3(2, 5, 3, false);
	// Ship s4(8, 7, 2, true);
	// Ship s5(7, 9, 3, true);

// hardest one
	// Ship s1(7, 1, 4, false);
	// Ship s2(5, 5, 5, true);
	// Ship s3(4, 7, 3, false);
	// Ship s4(8, 7, 2, true);
	// Ship s5(7, 9, 3, true);