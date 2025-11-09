//!Priority Scheduling Algorithm (Preemptive), O(n^2), O(n)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define ll long long
#define ld long double

struct task {
	string name;
	ll arrival, burst, priority, start = -1, complete = 0, remain = 0, wait = 0, tat = 0;
};

signed main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);


	ll n;
	cout << "Enter number of processes: ";
	cin >> n;

	vector<task> tasks(n);
	cout << "Enter <Name> <Arrival Time> <Burst Time> <Priority> for each process:\n";
	for (size_t i = 0; i < n; i++) {
		cin >> tasks[i].name >> tasks[i].arrival >> tasks[i].burst >> tasks[i].priority;
		tasks[i].remain = tasks[i].burst;
	}

	ll time = 0, completed = 0;
	ld total_wait = 0, total_tat = 0;

	while (completed < n) {
		ll indx = -1;
		ll min_pr = INT_MAX, min_br = INT_MAX;

		for (size_t i = 0; i < n; i++) {
			if (tasks[i].arrival <= time && tasks[i].remain > 0) {
				if (tasks[i].priority < min_pr ||
					(tasks[i].priority == min_pr && tasks[i].burst < min_br)) {
					min_pr = tasks[i].priority;
					min_br = tasks[i].burst;
					indx = i;
				}
			}
		}

		if (indx == -1) continue;
		time++;

		if (tasks[indx].remain == tasks[indx].burst) tasks[indx].start = time;
		tasks[indx].remain--;

		if (tasks[indx].remain == 0) {
			completed++;
			tasks[indx].complete = time;
			tasks[indx].tat = tasks[indx].complete - tasks[indx].arrival;
			tasks[indx].wait = tasks[indx].tat - tasks[indx].burst;
			total_wait += tasks[indx].wait;
			total_tat += tasks[indx].tat;
		}
	}

	cout << "\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n";
	for (auto& t : tasks) {
		cout << t.name << "\t" << t.arrival << "\t" << t.burst << "\t" << t.priority
			<< "\t" << t.complete << "\t" << t.tat << "\t" << t.wait << "\n";
	}

	cout << "\nAverage Waiting Time = " << total_wait / n << endl;
	cout << "Average Turnaround Time = " << total_tat / n << endl;

	return 0;
}