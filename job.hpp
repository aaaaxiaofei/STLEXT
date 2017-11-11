class Job {
public:
	int pid;
	int arrive_time;
	int burst_time;
	int waiting_time;
	int execution_time;

	Job() {}
	Job(int id, int arrive, int burst) :
		pid(id), arrive_time(arrive), burst_time(burst), waiting_time(0), execution_time(0) {}
	~Job() {}

};