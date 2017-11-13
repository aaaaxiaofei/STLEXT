#include <iostream>
#include "Job.hpp"
#include <deque>
using namespace std;

void round_robin(deque<Job>& job_queue, deque<Job>& done_queue, int quantum, int cur_time) {

	while (!job_queue.empty()) {
		Job j = job_queue.front();
		job_queue.pop_front();

		j.waiting_time += cur_time - j.execution_time - j.waiting_time - j.arrive_time;
		j.execution_time += quantum;

		cur_time += quantum;
		
		// Job finished
		if (j.execution_time >= j.burst_time) done_queue.push_back(j);
		// Job not finished
		else job_queue.push_back(j);
	}

	while (!done_queue.empty()) {
		Job j = done_queue.front();
		done_queue.pop_front();

		cout << "job " << j.pid 
			 << " waiting_time " << j.waiting_time << ", " 
		     << "turnaround time " << j.burst_time + j.waiting_time 
		     << endl;
	}

}

int strCmp(char string1[], char string2[] )
{
    for (int i = 0; ; i++)
    {
        if (string1[i] != string2[i])
        {
            return string1[i] < string2[i] ? -1 : 1;
        }

        if (string1[i] == '\0')
        {
            return 0;
        }
    }
}