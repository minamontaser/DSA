//! Round Robin Scheduling Algorithm, O(n^2), O(n)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define ll long long
#define ld long double

struct task {
	string name;
	ll arrival, burst, remain, start, wait, completion, tat;
};

signed main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	ll n, tq;
	cout << "No. processes: "; cin >> n;
	cout << "Time Quantum(TQ): "; cin >> tq;
	vector<task> tasks(n);
	for (size_t i = 0; i < n; i++) {
		cin >> tasks[i].name >> tasks[i].arrival >> tasks[i].burst;
		tasks[i].remain = tasks[i].burst;
	}
	ld total_wait = 0, total_tat = 0;
	ll completed = 0, time = 0;
	while (completed < n) {
		bool valid = false;
		for (size_t i = 0; i < n; i++) {
			if (tasks[i].arrival <= time && tasks[i].remain > 0) {
				valid = true;
				if (tasks[i].remain == tasks[i].burst) tasks[i].start = time;
				if (tasks[i].remain > tq) {
					time += tq;
					tasks[i].remain -= tq;
				}
				else {
					time += tasks[i].remain;
					tasks[i].remain = 0;
					tasks[i].completion = time;
					tasks[i].tat = tasks[i].completion - tasks[i].arrival;
					tasks[i].wait = tasks[i].tat - tasks[i].burst;
					total_wait += tasks[i].wait, total_tat += tasks[i].tat;
					completed++;
				}
			}
		}
		if (!valid) time++;
	}
	cout << "\nProcess\tAT\tBT\tST\tCT\tTAT\tWT\n";
	for (auto& t : tasks) {
		cout << t.name << "\t" << t.arrival << "\t" << t.burst << "\t" << t.start
			<< "\t" << t.completion << "\t" << t.tat << "\t" << t.wait << "\n";
	}

	cout << "\nAverage Waiting Time = " << total_wait / n << endl;
	cout << "Average Turnaround Time = " << total_tat / n << endl;

	return 0;
}