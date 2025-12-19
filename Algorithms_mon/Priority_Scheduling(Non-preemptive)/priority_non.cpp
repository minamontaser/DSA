//!Non-preemptive Priority Scheduling Algorithm
#include <iostream>
#include <string>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long
#define ld long double

inline void set_fast_io() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
}

struct task {
	string name;
	ll arrival, burst, start, wait, finish, tat, priority;
	bool done = false;
};

signed main() {

	set_fast_io();

	ll n; cin >> n;
	vector<task> tasks(n);
	for (task& it : tasks) cin >> it.name >> it.arrival >> it.burst >> it.priority;
	ld total_wait = 0, total_tat = 0;
	ll completed = 0, time = 0;
	while (completed < n) {
		ll indx = -1, max_pr = LLONG_MAX, min_br = LLONG_MAX;
		for (size_t i = 0; i < n; i++) {
			if (tasks[i].arrival <= time && !tasks[i].done) {
				if (tasks[i].priority < max_pr ||
					(tasks[i].priority == max_pr && tasks[i].burst < min_br)) {
					max_pr = tasks[i].priority, min_br = tasks[i].burst;
					indx = i;
				}
			}
		}
		if (indx == -1) {
			ll next_arrival = LLONG_MAX;
			for (task& it : tasks)
				if (!it.done)
					next_arrival = min(next_arrival, it.arrival);
			time = next_arrival;
			continue;
		}
		task& it = tasks[indx];
		it.done = true;
		it.start = time;
		time += it.burst;
		it.finish = time;
		it.tat = it.finish - it.arrival;
		it.wait = it.tat - it.burst;
		total_wait += it.wait, total_tat += it.tat;
		completed++;
	}

	cout << "\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n";
	for (auto& t : tasks) {
		cout << t.name << "\t" << t.arrival << "\t" << t.burst << "\t" << t.priority
			<< "\t" << t.finish << "\t" << t.tat << "\t" << t.wait << "\n";
	}

	cout << "\nAverage Waiting Time = " << total_wait / n << endl;
	cout << "Average Turnaround Time = " << total_tat / n << endl;

	return 0;
}